#   Creating genotypes that can be used with Ratio mapping of QTLs
#   This is different because we only have one measurement per two individuals
#   (c) 2010 Danny Arends - RUG

loadCross <- function(){
  #Load and transform genotypes
  mycross <- read.cross("csvr",file="complete_new.csv",genotypes=c("AA","AB"))
  class(mycross)[1] <- "riself"
  #Clean the markermap we dont trust
  cleancross <- calc.errorlod(mycross)
  cleancross <- drop.markers(cleancross, unique(top.errorlod(cleancross,cutoff=3)[,3]))
  cleancross <- drop.markers(cleancross, checkAlleles(mycross)[,1])
  mycross <- cleancross
  #return the cleaned object
  mycross
}

creategenotypes <- function(allids,mycross,crossorder){
  #holding the return genotypes
  geno <- NULL
  for(x in 1: nrow(allids)){
    if(!is.na(allids[x,1]) && !is.na(allids[x,2])){
      id1 <- translateID(allids[x,1],crossorder)
      id2 <- translateID(allids[x,2],crossorder)
      geno <- rbind(geno,createarraygeno(mycross,id1,id2))
    }
  }
  geno
}

translateID <- function(ID, crossorder){
  #uses the order.txt file to go from the microarray experiment IDs to the crossobject IDs
  val <- crossorder[which(crossorder[,1]==ID),2]
  val
}

createarraygeno <- function(cross,ind1,ind2){
  #Create a effect ratio genotype using the cross object and 2 crossobjectIDs
  allgenotypes <- pull.geno(cross)
  arraygeno <- NULL
  for(x in 1:dim(allgenotypes)[2]){
    m1 <- allgenotypes[ind1,x]
    m2 <- allgenotypes[ind2,x]
    if(m1==m2){
      arraygeno <- c(arraygeno,0)
    }
    if(m1 < m2){
      arraygeno <- c(arraygeno,1)
    }
    if(m1 > m2){
      arraygeno <- c(arraygeno,-1)
    }
  }
  arraygeno
}

createarraygenogroups <- function(cross,ind1,ind2){
  #Create a group ratio genotype using the cross object and 2 crossobjectIDs
  allgenotypes <- pull.geno(cross)
  arraygeno <- NULL
  for(x in 1:dim(allgenotypes)[2]){
    m1 <- allgenotypes[ind1,x]
    m2 <- allgenotypes[ind2,x]
    if(m1==m2){
      if(m1==1){
        arraygeno <- c(arraygeno,3)
      }else{
        arraygeno <- c(arraygeno,4)
      }
    }
    if(m1 < m2){
      arraygeno <- c(arraygeno,1)
    }
    if(m1 > m2){
      arraygeno <- c(arraygeno,2)
    }
  }
  arraygeno
}