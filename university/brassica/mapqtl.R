#   Main routine for parallel QTL mapping
#   (c) 2010 Danny Arends - RUG

mapallqtls <- function(genotypes, phenotypes,phenoinfo, multicore=TRUE, n.cores=4,batchsize=100){
  setwd(scriptdir)
  source("support/scripts.R")
  setwd(datadir)
  b <- proc.time()
  batches <- nrow(phenotypes) %/% batchsize
  lastbatchnum <- nrow(phenotypes) %% batchsize
  if(lastbatchnum > 0){
    batches = batches+1
  }
  bootstraps <- 1:nrow(phenotypes)
  if(multicore && ("snow" %in% installed.packages()[,1])){
    suppressWarnings(require(snow,quietly=TRUE))
    for(x in 1:(batches)){
      b <- proc.time()
      cat("INFO: Starting with batch",x,"/",batches,"\n")
      if(x==batches && lastbatchnum > 0){
        todo <- bootstraps[((batchsize*(x-1))+1):((batchsize*(x-1))+lastbatchnum)]
      }else{
        todo <- bootstraps[((batchsize*(x-1))+1):(batchsize*(x-1)+batchsize)]
      }	
      cl <- makeCluster(n.cores)
      clusterExport(cl, "scriptdir")
      clusterExport(cl, "datadir")
      clusterEvalQ(cl, setwd(scriptdir))
      clusterEvalQ(cl, source("support/scripts.R"))
      clusterEvalQ(cl, setwd(datadir))
      data <- parLapply(cl, todo, fun=mapQTL,genotypes=genotypes,phenotypes=phenotypes)
      n <- 1
      for(qtl in todo){
        cat(phenoinfo[qtl,], data[[n]], "\n", file="intermediateMapOutput.txt", append=T, sep="\t")
        n <- n+1
      }
      stopCluster(cl)
      e <- proc.time()
      cat("Time with SNOW:",round((e-b)[3], digits=3),"Seconds\n")
    }
  }else{
    data <- vector(mode = "list", length = nrow(phenotypes))
    for(x in 1:(batches)){
      b <- proc.time()
      cat("INFO: Starting with batch",x,"/",batches,"\n")
      if(x==batches && lastbatchnum > 0){
        todo <- bootstraps[((batchsize*(x-1))+1):((batchsize*(x-1))+lastbatchnum)]
      }else{
        todo <- bootstraps[((batchsize*(x-1))+1):(batchsize*(x-1)+batchsize)]
      }	
      for(num in todo){
        data[[num]] <- mapQTL(num,genotypes=genotypes,phenotypes=phenotypes)
      }
      e <- proc.time()
      cat("Time:",round((e-b)[3], digits=3),"Seconds\n")
    }
  }
  data
}


