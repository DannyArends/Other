#   Analysis of the 48 microarrays of the Brassica experiment
#   (c) 2010 Danny Arends - RUG

memory.limit(size = 4095)
library(qtl)
library(limma)
library(affy)
library(preprocessCore)

#GLOBAL VARIABLES PLEASE SET THEM TO YOUR SYSTEM
scriptdir = "D:/github/Brassica"
datadir = "F:/GBIC/Dunia"

setwd(scriptdir)

#Source the scripts so we have the functions
source("mapqtl.R")
source("loaddata.R")
source("creategenotypes.R")

setwd(datadir)

datafornormalization <- function(data){
  ratio <- NULL
  for(x in 1:(length(data)-2)){
    ratio <- cbind(ratio,data[[x]][,10])
  }
  ratio
}

QControll <- function(data){
  for(x in 1:length(data)){
    jpeg(file=paste("Dyeswap",x,".jpg"))
    op <- par(mfrow = c(1,2))
    plot(cbind(data[[x]][,18],data[[x]][,19]),xlab="Int 18",ylab="Int 19")
    abline(0,1,col="red")
    plot(cbind(log10(data[[x]][,18]),log10(data[[x]][,19])),xlab="Int 18",ylab="Int 19")
    abline(0,1,col="red")
    dev.off()  
  }
}

getratios <- function(data){
  ratio <- NULL
  for(x in 1:length(data)){
    cat("Ratio calculation array:",x,"/",length(data),"\n")
    ratio <- cbind(ratio,log10(data[[x]][,18])/log10(data[[x]][,19]))
  }
  colnames(ratio) <- paste("Array",1:length(data),sep="")
  rownames(ratio) <- rownames(data[[1]])
  ratio
}

getArrayIndividuals <- function(data){
  allids <- NULL
  for(x in 1:length(data)){
    locs <- gregexpr("([0-9]+)",attr(data[[x]],"file"),perl=T)
    ids <- NULL
    for(n in 1:length(locs[[1]])){
      loc <- locs[[1]][n]
      length <- attr(locs[[1]],"match.length")[n]
      if(loc!=1){
        val <- as.numeric(substr(attr(data[[x]],"file"),loc,loc+length))
      }else{
        val <- as.numeric(substr(attr(data[[x]],"file"),loc,length))
      }
      ids <- c(ids,val)
    }
    allids <- rbind(allids,ids)
  }
  allids
}

getphenotype <- function(num,allids,data){
  pheno <- NULL
  for(x in 1: nrow(allids)){
    if(!is.na(allids[x,1]) && !is.na(allids[x,2])){
      pheno <- c(pheno,data[[x]][num,10])
    }
  }
  pheno
}

donormalize <- function (){
  data <- loaddata()
  #Get the columns we want
  dataformat <- datafornormalization(data)
  #Normalize the ratio data columns
  dataNormalized <- normalize.quantiles(dataformat)
  colnames(dataNormalized) <- paste("Array",1:(length(data)-2),sep="")
  #Save results ? bind the headers n stuff
  dataNormalizedInfo <- cbind(data[[1]][,1:3],dataNormalized)
  write.table(dataNormalizedInfo,file="48ArraysNormalized.txt",sep="\t",row.names=F)
  dataNormalizedInfo <- NULL
  phenoinfo <- data[[1]][,1:3]
  phenoinfo <- as.matrix(phenoinfo)
}

loadnormalizeddata <- function(){
  #Read which individuals are on the arrays
  allids <- read.csv("ArrayToSample.txt",sep="\t",row.names=1,header=F)
  #we dont need the last 2 arrays
  allids <- allids[1:48,]
  #Normalizeddata from file
  dataNormalizedInfo <- read.csv(file="48ArraysNormalized.txt",sep="\t",header=T)
  dataNormalized <- dataNormalizedInfo[,4:51]
  phenoinfo <- dataNormalizedInfo[,1:3]
  phenoinfo <- as.matrix(phenoinfo)
  crossorder <- read.csv("order.txt",header=T,sep="\t")
  mycross <- loadCross()
  #Now create Ratio genotypes
  genotypes <- creategenotypes(allids,fill.geno(mycross),crossorder)
  return(list(mycross,genotypes,dataNormalized,phenoinfo,allids))
}

doQTL <- function(genotypes, dataNormalized, phenoinfo){
  QTLs <- mapallqtls(genotypes, dataNormalized, phenoinfo)
}

readQTLresults <- function(file="QTLallRegression.txt"){
  #loading 170MB of QTL profiles from file (quite heavy)
  QTLs <- read.table(file=file,sep="\t")
  QTLs
}


analyse <- function(){
  #Read the QTL results form file
  QTLs <- readQTLresults()
  #Read the normalized dataset, order, etc from file
  #Analysis <- loadnormalizeddata()
  interest <- read.table(file="underinvestigation.txt",sep="\t")
  mycross <- loadCross()
  #QTLs <- QTLs[which(QTLs[,2] %in% as.character(interest[,1])),]
  #reduce the results and make an 'heatmap'
  reduceQTLres(mycross,QTLs,interest)
}

reduceQTLres <- function(cross,QTLs,interest,start=1,stop=23){
  #reduce QTL results by only extracting between start and stop
  reduced <- NULL
  count <- 1
  names <- NULL
  for(x in start:stop){
    name <- as.character(interest[x,1])
    names <- c(names,as.character(paste(x,"-",interest[x,2],sep="")))
    cat(x,name,"\n")
    reduced <- rbind(reduced,QTLs[which(QTLs[,2]==name),])
  }
  image(4:(ncol(reduced)-1),start:stop,t(as.matrix(reduced[,4:(ncol(reduced)-1)])),xlab="Markers",ylab="Expressions",breaks=c(0,2,4,6,8,10,100),col=c("white","lightblue","lightgreen","green","orange","red"))
  loc <- 1
  for(x in nmar(cross)){
    abline(v=loc)
    if(loc != 1){
      loc <- loc+x
    }else{
      loc <- x
    }
  }
  reduced <- reduced[,1:(ncol(reduced)-1)]
  rownames(reduced) <- names
  reduced
}


reduceit <- function(genotypes,interest,normdata,start=1,stop=23){
  #(RE)Calculate QTL results by only extracting between start and stop
  QTLs <- NULL
  for(x in start:stop){
    name <- as.character(interest[x,1])
    id <- which(normdata[,2]==name)
    cat(name,id,"\n",sep="\t")
    QTLs <- rbind(QTLs,mapQTL(genotypes,as.numeric(normdata[id,4:51])))
  }
  image(1:(ncol(QTLs)),start:stop,t(as.matrix(QTLs)),xlab="Markers",ylab="Expressions",breaks=c(0,2,4,6,8,10,100),col=c("white","lightblue","lightgreen","green","orange","red"))
  QTLs
}

plotall <- function(mycross,QTLs,interest,n_p_plot=75){
  #Does plotting of all genes in heatmap style using a variable number of traits per plot (n_p_plot)
  start <- 1
  stop <- n_p_plot
  while(start < nrow(interest)){
    jpeg(filename = paste("Trait",start,"_to_",stop,".jpg"), width = 1024, height = 800)
    reduceQTLres(mycross,QTLs,interest,start,stop)
    dev.off()
    start <- start + n_p_plot
    stop <- stop + n_p_plot
    if(stop > nrow(interest)) stop <-  nrow(interest)
  }
}

getinteresting <- function(QTLs,interest,minlod=3.5){
 QTLres <- NULL
 names <- NULL
 for(x in 1:nrow(interest)){
    cat(x,"/",nrow(interest),"\n")
    name <- as.character(interest[x,1])
    if(max(QTLs[which(QTLs[,2]==name),4:ncol(QTLs)],na.rm=T) > minlod){
      names <- c(names,as.character(paste(name,"-",interest[x,2],sep="")))
      QTLres <- rbind(QTLres,QTLs[which(QTLs[,2]==name),])
    }
  }
  rownames(QTLres) <- names
  QTLres
}

getallabove <- function(QTLs,minlod=3.5){
 QTLres <- NULL
 names <- NULL
 for(x in 1:nrow(QTLs)){
    cat(x,"/",nrow(QTLs),"\n")
    if(max(QTLs[x,4:ncol(QTLs)],na.rm=T) > minlod){
      names <- c(names,QTLs[x,2])
      QTLres <- rbind(QTLres,QTLs[x,])
    }
  }
  rownames(QTLres) <- names
  QTLres
}


groupclusteredheatmap <- function(clusteredheatmapresult, height){
  items <- cut(clusteredheatmapresult$Rowv,h=height)$lower
  groups <- vector(length(items), mode="list")
  cnt <- 1
  for(x in items){
    groups[[cnt]] <-labels(x)
    cnt <- cnt+1
  }
  groups
}


plotProfiles <- function(cross,QTLresults,clusteredheatmapresult,cutoff,method=c("mean","median")){
  groups <- groupclusteredheatmap(clusteredheatmapresult,cutoff)
  supported <- c("mean","median")
  method <- pmatch(method, supported)
  r <- scanone(cross)
  cnt <- 1 
  for(x in groups){
    profiles <- as.matrix(QTLresults[x,4:229])
    mlod <- max(profiles)
    jpeg(filename = paste("ClusterProfiles_",cnt,"_at_",cutoff,".jpg"), width = 1024, height = 800)
      plot(r,ylim=c(0,mlod),col="white",lwd=0,ylab="LOD score",xlab="Markers",main="Multiple profiles")
    
      for(pr in 1:nrow(profiles)){
        r[,3] <- as.numeric(profiles[pr,])
        plot(r, add=T,col="blue",lwd=0.5,lty=2)
      }
      if(method==1) r[,3] <- apply(profiles,2,mean)
      if(method==2) r[,3] <- apply(profiles,2,median)
      plot(r, add=T,col="black",lwd=4)
    dev.off()
    cnt <- cnt+1
  }
}

plotprofiles <- function(cross,QTLs,interest,minlod=3.5,start=1,stop=23){
  #plots the profiles above minlod between start and stop
  scanobj <- scanone(cross)
  for(x in 1:nrow(interest)){
    name <- as.character(interest[x,1])
    if(max(QTLs[which(QTLs[,2]==name),4:ncol(QTLs)],na.rm=T) > minlod){
      jpeg(filename = paste("Profile_",x,"_",name,".jpg"), width = 1024, height = 800)
        scanobj[,3] <- as.numeric(QTLs[which(QTLs[,2]==name),4:(ncol(QTLs)-1)])
        plot(scanobj)
      dev.off()
    }
  }
}
