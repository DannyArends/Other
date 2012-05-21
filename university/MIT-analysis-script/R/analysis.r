######################################################################
#
# analysis.R
#
# copyright (c) 2011-2011, Musa A. Hasan and Danny Arends
# last modified Jun, 2011
# first written ??, 2011
#
#     This program is free software; you can redistribute it and/or
#     modify it under the terms of the GNU General Public License,
#     version 3, as published by the Free Software Foundation.
# 
#     This program is distributed in the hope that it will be useful,
#     but without any warranty; without even the implied warranty of
#     merchantability or fitness for a particular purpose.  See the GNU
#     General Public License, version 3, for more details.
# 
#     A copy of the GNU General Public License, version 3, is available
#     at http://www.r-project.org/Licenses/GPL-3
# 
# Contains: analysis pipeline for MIT
#
######################################################################

rm(list=ls())

data_location = "c://QTLdata/"
data_file = "AXBXAall.csv"
map_file = paste(data_location,"map.txt",sep="")
annotation_file = paste(data_location,"annotgenomefinal.txt",sep="")

output_file = "C:/QTLdata/axball020711.txt"
output_rdata = "C:/QTLdata/axball020713.RDATA"

library(qtl)
axball <- read.cross("csv", data_location, data_file, genotypes=c("AA","BB"))
class(axball)[1] <- "risib"
axball<-jittermap(axball)
axball<-est.rf(axball) #estimate recombination fraction
axball<-calc.genoprob(axball, step=1, error.prob=0.01)
axball<-sim.geno(axball,step=1, n.draws=100, error.prob=0.01)

output<-vector("list", (nphe(axball)-1))
output.perm<-vector("list", (nphe(axball)-1))
output.covar<-vector("list", (nphe(axball)-1))
output.intcovar<-vector("list", (nphe(axball)-1))
output.covarperm<-vector("list", (nphe(axball)-1))
output.intcovarperm<-vector("list", (nphe(axball)-1))

titles<-c("pheno number","phenotype","chromosome","marker","lodintflankingmarkers","bayesintflankingmarkers","position cM","position Mb","lodintflankingposcM","bayesintflankingposcM","lodintflankingposMb","bayesintflankingposMb","LOD-score", "Threshold P=0.1", "Threshold P=0.05","phenotype","chromosome-addcovar","marker-addcovar", "position_cM-addcovar", "LOD-score-addcovar", "phenotype","chromosome-intcovar","marker-intcovar", "position_cM-intcovar", "LOD-score-intcovar","Threshold P=0.1-addcovar", "Threshold P=0.05-addcovar", "Threshold P=0.1-intcovar", "Threshold P=0.05-intcovar")
emptytitles<-c("","")
write.table(titles,file=output_file,sep="\t",append=TRUE,eol="\t",col.names=FALSE,row.names=FALSE)

#you can look in the R manual write.table command
i<-0
j<-0
for(i in 1:(nphe(axball)-1)){
  axball$pheno[,i]<-as.numeric(axball$pheno[,i])
}

i<-0

#Start loop but for some reason sex is always added as a phenotype and therefore we don't want to go till the end
  #(Danny: Todo: Drop the last one then to simplyfy the code ;)
  #- Primary scan for each phenotype using imputation no permutations at this point
  #- Find the the marker associated with the peak LOD score
  #- Find the chromosome associated the peak LOD score (TODO: The rare cases that there are two equal peaks it will just pick one)
  #- Get the cM associated the peak LOD score
  #- Only use the real markers (TODO: Why are imputed ones not good ??)
  #- Find all the names of the markers on the chromosome associated with peak LOD score
  #- Find all the postion of the marker with max lod score (relative to other markers)
  #- Calculates LOD interval within 1.5 of max LOD score and uses closest markers
  #- Then - Get the flanking positions
  #- Get the flanking marker names this roundabout method is because i dont know r (TODO)
  #- Get the map table to convert to physical location
  #- Convert all positions we found to physical location
for(j in 1:(nphe(axball)-1)){

  output[[j]]<-scanone(axball, pheno.col=j, method="imp", model="normal", n.perm=0)
  maxmarker <- rownames(max(output[[j]]))
  maxchr <- output[[j]][maxmarker, 1]
  if(length(maxchr) > 1){ 
    #Danny: this is a bug why Choose 1 at random ???
    maxchr <- sample(maxchr, 1)
  }
  maxcm <- output[[j]][maxmarker, 2]
  maxrealmarker<-find.marker(axball, maxchr, maxcm)
  maxchrallmarkers<-colnames(axball$geno[[maxchr]]$data)
  maxchrmaxmarkerpos<-which(maxchrallmarkers==maxrealmarker)

  lodinterval<-lodint(output[[j]],maxchr,1.5,expandtomarkers=TRUE)
  lodintpos<-lodinterval$pos
  llen <- length(lodintpos)
  flank1<-lodintpos[1]
  flank2<-lodintpos[llen]
  lodintflank<-paste(flank1,flank2,sep='--')
  flankmark1<-find.marker(axball,chr=maxchr,pos=flank1)
  flankmark2<-find.marker(axball,chr=maxchr,pos=flank2)
  lodintflankmark<-paste(flankmark1,flankmark2,sep='--')

  bayinterval<-bayesint(output[[j]],maxchr,0.95,expandtomarkers=TRUE)
  bayintpos<-bayinterval$pos
  alen <- length(bayintpos)
  flank3<-bayintpos[1]
  flank4<-bayintpos[alen]
  bayintflank<-paste(flank3,flank4,sep='--')
  flankmark3<-find.marker(axball,chr=maxchr,pos=flank3)
  flankmark4<-find.marker(axball,chr=maxchr,pos=flank4)
  bayintflankmark<-paste(flankmark3,flankmark4,sep='--')
  
  map <- read.table(map_file,header=T)
  map.Locus<-map$Locus
  map.Mb<-map$Mb
  map.Chr<-map$Chr
  maxmb<-map.Mb[map.Locus==maxrealmarker]

  flankphysical1<-map.Mb[map.Locus==flankmark1]
  flankphysical2<-map.Mb[map.Locus==flankmark2]
  flankphysical3<-map.Mb[map.Locus==flankmark3]
  flankphysical4<-map.Mb[map.Locus==flankmark4]
  lodintflankphys<-paste(flankphysical1,flankphysical2,sep='--')
  bayintflankphys<-paste(flankphysical3,flankphysical4,sep='--')

  anno <- read.table(annotation_file,header=T)
  anno.chrom <- anno$chrom
  L <-anno$chrom==as.character(maxchr)
  chromosome <- anno[L,]
  chromosome.start <- chromosome$txStart
  chromosome.end <- chromosome$txEnd
  chromosome.names <- chromosome$name2
  flankphysical1bp<-flankphysical1*1000000
  flankphysical2bp<-flankphysical2*1000000
  genes <- chromosome.names[((chromosome.end>flankphysical1bp)&(chromosome.end<flankphysical2bp))|((chromosome.start>flankphysical1bp)&(chromosome.start<flankphysical2bp))]

  #Danny: From here we seem to start writing output

  #This will write the name of the phenotype we are investigating
  #This will write the chromosome associated with the max LOD score
  #This will write the name of the marker associated with the peak lod score
  #This will write in the flanking markers for the lodint
  #This will write in the flanking markers for the bayesint
  #This will write the position in cM of the marker associated with the peak lod score
  #This writes in the physical location of the peak lod score
  #Writes position of lodint
  #Writes in the position of bayesint
  #Writes physical position of lodint
  #Writes physical position of bayesint
  #This will write the maximum LOD score
  write.table(genes,file = "c://QTLdata/genes.txt",append = TRUE)
  write.table("",file=output_file,sep="\t",append=TRUE,eol="\r",col.names=FALSE,row.names=FALSE)	#New line
  write.table(j,file=output_file,sep="\t",append=TRUE,eol="\t",col.names=FALSE,row.names=FALSE)
  write.table(names(axball$pheno)[c(j)],file=output_file,sep="\t",append=TRUE,eol="\t",col.names=FALSE,row.names=FALSE)
  write.table(maxchr,file=output_file,sep="\t",append=TRUE,eol="\t",col.names=FALSE,row.names=FALSE)
  write.table(maxrealmarker,file=output_file,sep="\t",append=TRUE,eol="\t",col.names=FALSE,row.names=FALSE)
  write.table(lodintflankmark,file=output_file,sep="\t",append=TRUE,eol="\t",col.names=FALSE,row.names=FALSE)
  write.table(bayintflankmark,file=output_file,sep="\t",append=TRUE,eol="\t",col.names=FALSE,row.names=FALSE)
  write.table(maxcm,file=output_file,sep="\t",append=TRUE,eol="\t",col.names=FALSE,row.names=FALSE)
  write.table(maxmb,file=output_file,sep="\t",append=TRUE,eol="\t",col.names=FALSE,row.names=FALSE)
  write.table(lodintflank,file=output_file,sep="\t",append=TRUE,eol="\t",col.names=FALSE,row.names=FALSE)
  write.table(bayintflank,file=output_file,sep="\t",append=TRUE,eol="\t",col.names=FALSE,row.names=FALSE)
  write.table(lodintflankphys,file=output_file,sep="\t",append=TRUE,eol="\t",col.names=FALSE,row.names=FALSE)
  write.table(bayintflankphys,file=output_file,sep="\t",append=TRUE,eol="\t",col.names=FALSE,row.names=FALSE)
  write.table(max(output[[j]][,3]),file=output_file,sep="\t",append=TRUE,eol="\t",col.names=FALSE,row.names=FALSE)

  #DANNY: TODO Change this into a function (so we can do do it separate)
  #Permutation take so long only do permutation if there is a lod score > 3 somewhere. you can change this value 		
  if (max(output[[j]][,3]) > 3) {
    output.perm[[j]]<-scanone(axball, pheno.col=j, method="imp", model="normal", n.perm=100)
    print(j)
    write.table(quantile(output.perm[[j]],0.95),file=output_file,sep="\t",append=TRUE,eol="\t",col.names=FALSE,row.names=FALSE)
    write.table(quantile(output.perm[[j]],0.99),file=output_file,sep="\t",append=TRUE,eol="\t",col.names=FALSE,row.names=FALSE)
    
    #write(output[[j]][,3], ncolumns=85, append=TRUE, sep="\t",file=output_file)
    #This line has to be changed the idea of it was to put the LOD score at each marker here but in this cross there are too many the nr 85 is nr of markers from IIxIII cross
    if (max(output[[j]][,3]) > 3)  {
      #Danny: TODO make it into a function
      #This will start the loop to look for other QTLs by making the previous one a cofactor if the maximum Lod score is higher than the P=0.10 threshold
      output.covar[[j]] <- scanone(axball, pheno.col=j, method="imp", model="normal", addcovar=cbind(axball$geno[[maxchr]]$data[,maxchrmaxmarkerpos]), n.perm=0)
      output.intcovar[[j]] <- scanone(axball, pheno.col=j, method="imp", model="normal", addcovar=cbind(axball$geno[[maxchr]]$data[,maxchrmaxmarkerpos]), intcovar=cbind(axball$geno[[maxchr]]$data[,maxchrmaxmarkerpos]),n.perm=0)			       		
      maxmarkercovar <- rownames(max(output.covar[[j]]))
      maxmarkerintcovar <- rownames(max(output.intcovar[[j]]))
      maxcovarcm <- output[[j]][maxmarkercovar, 2]
      maxintcovarcm <- output[[j]][maxmarkerintcovar, 2]
      maxchrcovar <- output.covar[[j]][maxmarkercovar, 1]
      maxchrintcovar <- output.intcovar[[j]][maxmarkerintcovar, 1]
      maxrealmarkercovar<-find.marker(axball, maxchrcovar, maxcovarcm)
      maxrealmarkerintcovar<-find.marker(axball, maxchrintcovar, maxintcovarcm)
      
      write.table(names(axball$pheno)[c(j)],file=output_file,sep="\t",append=TRUE,eol="\t",col.names=FALSE,row.names=FALSE)
      write.table(maxchrcovar,file=output_file,sep="\t",append=TRUE,eol="\t",col.names=FALSE,row.names=FALSE)			        	
      write.table(maxrealmarkercovar,file=output_file,sep="\t",append=TRUE,eol="\t",col.names=FALSE,row.names=FALSE)
      write.table(maxcovarcm,file=output_file,sep="\t",append=TRUE,eol="\t",col.names=FALSE,row.names=FALSE)	
      write.table(max(output.covar[[j]][,3]),file=output_file,sep="\t",append=TRUE,eol="\t",col.names=FALSE,row.names=FALSE)
      write.table(names(axball$pheno)[c(j)],file=output_file,sep="\t",append=TRUE,eol="\t",col.names=FALSE,row.names=FALSE)
      write.table(maxchrintcovar,file=output_file,sep="\t",append=TRUE,eol="\t",col.names=FALSE,row.names=FALSE)			        	
      write.table(maxrealmarkerintcovar,file=output_file,sep="\t",append=TRUE,eol="\t",col.names=FALSE,row.names=FALSE)
      write.table(maxintcovarcm,file=output_file,sep="\t",append=TRUE,eol="\t",col.names=FALSE,row.names=FALSE)	
      write.table(max(output.intcovar[[j]][,3]),file=output_file,sep="\t",append=TRUE,eol="\t",col.names=FALSE,row.names=FALSE)
      #Danny: TODO another function
      if (max(output.covar[[j]][,3]) > 3) {
        #Same thing, if the new LOD score > 3 start permutations
        output.covarperm[[j]] <- scanone(axball, pheno.col=j, method="imp", model="normal", addcovar=cbind(axball$geno[[maxchr]]$data[,maxchrmaxmarkerpos]), n.perm=100)
        write.table(quantile(output.covarperm[[j]],0.90),file=output_file,sep="\t",append=TRUE,eol="\t",col.names=FALSE,row.names=FALSE)
        write.table(quantile(output.covarperm[[j]],0.95),file=output_file,sep="\t",append=TRUE,eol="\t",col.names=FALSE,row.names=FALSE)
        #write(output.covar[[j]][,3], ncolumns=85, append=TRUE, sep="\t",file="C:/QTLdata/axball020711_COVAR.txt")
      }else{
        write.table(emptytitles,file=output_file,sep="\t",append=TRUE,eol="\t",col.names=FALSE,row.names=FALSE)
      }
      if (max(output.intcovar[[j]][,3]) > 3) {
        #Same thing, if the new LOD score > 3 start permutations
        output.intcovarperm[[j]] <- scanone(axball, pheno.col=j, method="imp", model="normal", addcovar=cbind(axball$geno[[maxchr]]$data[,maxchrmaxmarkerpos]), intcovar=cbind(axball$geno[[maxchr]]$data[,maxchrmaxmarkerpos]),n.perm=100)
        write.table(quantile(output.intcovarperm[[j]],0.90),file=output_file,sep="\t",append=TRUE,eol="\t",col.names=FALSE,row.names=FALSE)
        write.table(quantile(output.intcovarperm[[j]],0.95),file=output_file,sep="\t",append=TRUE,eol="\t",col.names=FALSE,row.names=FALSE)
        #write(output.intcovar[[j]][,3], ncolumns=85, append=TRUE, sep="\t",file="C:/QTLdata/axball020711_COVAR.txt")
      }else{
        write.table("",file=output_file,sep="\t",append=TRUE,eol="\r",col.names=FALSE,row.names=FALSE)
      }
    }else{
      write.table("",file=output_file,sep="\t",append=TRUE,eol="\r",col.names=FALSE,row.names=FALSE)
    }
  }else{
    write.table("",file=output_file,sep="\t",append=TRUE,eol="\r",col.names=FALSE,row.names=FALSE)
  }
}
sink()
save(list=ls(all=TRUE), file=output_rdata)