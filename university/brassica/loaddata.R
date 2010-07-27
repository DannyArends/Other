#   Main routine for parallel dataloading
#   (c) 2010 Danny Arends - RUG

loaddata <- function(uniqueelement="_vs_", multicore=TRUE, n.cores=3, sep="\t", ...){
  setwd(scriptdir)
  source("support/scripts.R")
  setwd(datadir)
  b <- proc.time()
  cnt <- 0;
  filelist <- NULL
  for(x in dir()){
    if(!is.na(grep(uniqueelement,x)&&1)){
      cnt <- cnt+1
      filelist <- c(filelist,x)
    }
  }
  cat(cnt," files matched against",uniqueelement,"\n")
  if(multicore && ("snow" %in% installed.packages()[,1])){
    suppressWarnings(require(snow,quietly=TRUE))
    cl <- makeCluster(n.cores)
    clusterExport(cl, "scriptdir")
    clusterExport(cl, "datadir")
    clusterEvalQ(cl, setwd(scriptdir))
    clusterEvalQ(cl, source("support/scripts.R"))
    clusterEvalQ(cl, setwd(datadir))
    data <- parLapply(cl,1:cnt, fun=loader,filelist=filelist,sep=sep)
    stopCluster(cl)
    e <- proc.time()
    cat("Time loading with SNOW:",round((e-b)[3], digits=3),"Seconds\n")
  }else{
    data <- vector(mode = "list", length = cnt)
    for(x in 1:cnt){
      data[[cnt]] <- loader(x,filelist=filelist,sep=sep,...)
    }
    e <- proc.time()
    cat("Time loading:",round((e-b)[3], digits=3),"Seconds\n")
  }
  data
}


