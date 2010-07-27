#   Basic scripts that can be executed in parallel
#   (c) 2010 Danny Arends - RUG

loader <- function(x, filelist, sep, ...){
  result <- read.csv(filelist[x], sep=sep, ...)
  attr(result,"file") <- filelist[x]
	result
}

mapQTL <- function(x,genotypes, phenotypes){
  LODvalues <- NULL
  for(marker in 1:ncol(genotypes)){
    genomodel <- lm(phenotypes[x,] ~ genotypes[,marker])
    Pvalues <- anova(genomodel)[[5]]
    LODvalues <- c(LODvalues,-log10(Pvalues[length(Pvalues)-1]))
  }
  LODvalues
}


mapQTL <- function(genotypes, phenotypes){
  LODvalues <- NULL
  for(marker in 1:ncol(genotypes)){
    genomodel <- lm(phenotypes ~ genotypes[,marker])
    Pvalues <- anova(genomodel)[[5]]
    LODvalues <- c(LODvalues,-log10(Pvalues[1]))
  }
  LODvalues
}
