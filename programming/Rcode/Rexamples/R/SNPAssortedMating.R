#####################################################################
#
# AssortedMating.R
#
# copyright parent_check (c) 2009, Danny Arends
# last modified Apr, 2009
# first written Apr, 2009
# 
# Contains: assortedmating
#
######################################################################

plotDIR <- function(dir = "D:\\GBIC\\Lude\\Resultsgood", which = 2){
	setwd(dir)
	cnt <- 0
	genome <- NULL
	m_markers <- 1
	m_done <- 0
	for(x in dir()){
		if(!is.na(grep("res",x)==1&&1)){
		chr <- read.table(x,row.names=1,header=FALSE,sep="\t")
		markers <- nrow(chr)
		m_done <- m_done+markers
		score <- max(abs(chr))
		cnt <- cnt+1
		m_markers <- c(m_markers,m_done)
		}
	}
	c <- c("black","gray")
	cnt <- 0
	names <- NULL
	if(which==1){
		plot(x=c(1,m_done),y=c(0,2000),main="Population Score",xlab="Markers",ylab="Chi^2",type="n")
	}else{
		if(which==2){
			plot(x=c(1,m_done),y=c(-150,150),main="InbreadingScores",xlab="Markers",ylab="Chi^2", type="n")
		}else{
			plot(x=c(1,m_done),y=c(-150,150),main="AMScores",xlab="Markers",ylab="Chi^2", type="n")
		}
	}
	for(x in dir()){
		if(!is.na(grep("res",x)==1&&1)){
		cnt <- cnt+1
		names <- c(names,x)
		chr <- read.table(x,row.names=1,header=FALSE,sep="\t")
		colo <- (cnt%%length(c))
		if(colo==0){colo<- length(c)}
		points(x=m_markers[cnt]+1:length(chr[,which]),chr[,which],type="h",col=c[colo], main=x)
		}
	}
	names <- gsub("res","",names)
	names <- gsub(".txt","",names)
	legend("topright",names,lty=1,col=c,cex=.6,ncol=2)
}

plotLength<- function(x,LengthMatrix,name=TRUE,which = 2){
	if(which==1){
		text <- "Inbreading (Chi^2)"
	}else{
		text <- "Deviation from random mating(Chi^2)"
	}
	if(name){
		lbls <- paste("Chr ",LengthMatrix[,1],"_",LengthMatrix[,2],sep="")
		size=0.5
	}else{
		lbls <- rownames(LengthMatrix)
		size=0.7
	}
	plot(x[[2]],type="b",axes=0,xlab="",ylab=text)
	box()
	Axis(side=1,at=1:37,labels=lbls,cex.axis=size,las=0.5,las=2)
	Axis(side=2)
}

assortedmating.init <- function(){
	workD="D:\\GBIC\\Lude\\DataDanny"
	setwd(workD)	
	snps <- as.matrix(read.table("length.txt"))
	LengthMatrix <- NULL
	for(x in dir()[grep("Chr",dir())]){
		if(is.na(grep("res",x)==1&&1)){
			cat("Reading",x,"\n")
			data <- read.table(x,row.names=1)
			for(searching in 1:nrow(snps)){
				chr <- as.numeric(snps[searching,2])
				if(chr %in% data[,1]){
					bp <- as.numeric(snps[searching,3])
					cat("SNPs in length.txt on this chromosome:",snps[searching,1:3],"\n")
					smaller <- which(data[,2]<(bp+1000))
					larger <- which(data[,2]>(bp-1000))
					intersect(smaller,larger)
					if(!is.na(intersect(smaller,larger)&&1)){
						for( y in intersect(smaller,larger)){
							cat("->",rownames(data)[y],data[y,1],data[y,2],"\n")
							LengthMatrix <- rbind(LengthMatrix,data[y,])
						}
					}
				}
			}
		}
	}
	LengthMatrix
}


doDir <- function(){
setwd("D:\\GBIC\\Lude\\DataDanny")
order <- as.vector(read.csv("ChipIDOrderInGenotypeFiles.txt",header=FALSE,sep="\n"))
info <- read.csv("ChipIDToSampleInformation.txt",row.names=1,header=TRUE,sep="\t")
coln <- c("Chr","Pos",as.vector(order[,1]))
for(x in dir()){
	if(!is.na(grep("Chr",x)==1&&1)){
	if(is.na(grep("res",x)==1&&1)){
		data <- read.csv(x,row.names=1,header=TRUE,sep="\t")
		colnames(data) <- coln
		assortedmating(data,info,1,nrow(data)-1,paste("res",x,sep=""),plot=FALSE)
	}
	}
}
}

init <- function(){
setwd("D:\\GBIC\\Lude\\RAW")
data <- read.csv("Chr2.txt",row.names=1,sep="\t")
order <- as.vector(read.csv("ChipIDOrderInGenotypeFiles.txt",header=FALSE,sep="\n"))
info <- read.csv("ChipIDToSampleInformation.txt",row.names=1,header=TRUE,sep="\t")
coln <- c("Chr","Pos",as.vector(order[,1]))
colnames(data) <- coln
}

initplottingqq <- function(name="Chromosome 1",resF="resChr1.txt"){
	setwd("D:\\GBIC\\Lude\\Resultsgood")
	r <- read.csv(resF,row.names=1,header=FALSE,sep="\t")
	plottingqq(name,r[,3],3)
}

readallres <- function(){
	setwd("D:\\GBIC\\Lude\\Resultsgood")
	reslist <- NULL
	for(x in dir()){
		if(!is.na(grep("Chr",x)==1&&1)){
			if(!is.na(grep("res",x)==1&&1)){
				cat(x,"\n")
				data <- read.csv(x,row.names=1,header=FALSE,sep="\t")
				reslist <- rbind(reslist,data)
			}
		}
	}
	reslist
}

ScaledownusingHW <- function(result,cutoff){
	result[result[,1]<cutoff,]
}

AboveAM <- function(result,cutoff_hw,cutoff_am){
	adhereHW <- ScaledownusingHW(result,cutoff_hw);
	uber <-  adhereHW[adhereHW[,3]>cutoff_am,]
	write.table(file=paste("HW<"+cutoff_hw+"AM<"+cutoff_am+".txt",sep=""),uber,sep="\t",quote=F,row.names=F,col.names=F)
}
addLoc <- function(name){

}

plottingqq <- function(name,scores,df){
	pos <- scores[scores>=0]
	neg <- scores[scores<0]
	exp_pos <- rchisq(length(pos),df=df)
	exp_neg <- -rchisq(length(neg),df=df)
	colors = rep("blue",length(neg))
	colors = c(colors,rep("green",length(pos)))
	
	plot(-75:150,-75:150,main=paste(name,"DegFree:",df),xlab="Observed Chi^2",ylab="Expected Chi^2",type="n")
	points(sort(c(pos,neg)),sort(c(exp_pos,exp_neg)),pch=19,lwd=0.1,col=colors)
	lines(-max(abs(scores)):max(abs(scores)),-max(abs(scores)):max(abs(scores)),col="black")
	legend("bottomright", legend = c("Homozygote", "Hetrozygote"),col=c("blue","green"),pch=19,title="Chi^2 Scores")
}

assortedmating <- function(data,info,start=1,number=0,name="Test.txt",plot=TRUE,verbose=TRUE,logger=FALSE){
	PopulationScores <- NULL		#Teststatistic results holder
	DirScores <- NULL
	SPopulationScores <- NULL				#Scaled Teststatistic result holder
	InbreadingScores <- NULL				#Inbreading coeficient result holder
	ReturnMatrix <- c("",0,0,0,0)			#Final scoring matrix
	pDir <- NULL				#ParentalMatingSchema LikelyhoodScores
	PopScores <- NULL
	ParScores <- NULL
	ourcat(logger,"AM","INFO: Analyzing",number,"SNPMarkers\n",verbose=verbose)
	
	plist <- NULL
	for(locus in start:(start+number)){
		ourcat(logger,"AM","-----------------------------------------------------------------------\n",verbose=verbose)
		ourcat(logger,"AM","Starting with locus:",locus,"\n",verbose=verbose)
		ourcat(logger,"AM","-----------------------------------------------------------------------\n",verbose=verbose)
		ind_num <- 1
		nparents <- 0
		ObservedAllel <- c(0,0,0,0)
		Observed <- rep(0,10)
		Expected <- rep(0,10)
		ExpectedAllel <- c(0,0,0,0)
		Observedtable <- cbind(rep(0,10),rep(0,10),rep(0,10),rep(0,10),rep(0,10),rep(0,10),rep(0,10),rep(0,10),rep(0,10),rep(0,10))
		Expectedtable <- cbind(rep(0,10),rep(0,10),rep(0,10),rep(0,10),rep(0,10),rep(0,10),rep(0,10),rep(0,10),rep(0,10),rep(0,10))
		names(ObservedAllel) <- c("A","C","G","T")
		names(ExpectedAllel) <- c("A","C","G","T")
		rownames(Observedtable) <- c("AA","AC","AG","AT","CC","CG","CT","GG","GT","TT")
		names(Observed) <- c("AA","AC","AG","AT","CC","CG","CT","GG","GT","TT")
		names(Expected) <- c("AA","AC","AG","AT","CC","CG","CT","GG","GT","TT")
		rownames(Expectedtable) <- c("AA","AC","AG","AT","CC","CG","CT","GG","GT","TT")
		colnames(Observedtable) <- c("AA","AC","AG","AT","CC","CG","CT","GG","GT","TT")
		colnames(Expectedtable) <- c("AA","AC","AG","AT","CC","CG","CT","GG","GT","TT")
		#cat("here",ind_num)
		for(ind in rownames(info)){
			#cat("starting with:",ind,"\n")
			colnum <- which(colnames(data)==ind)
			#cat(ind,"colnum in data:",colnum,"\n")
			#cat(ind,"rownum in info:",ind_num,"\n")
			ind.status <- info[ind_num,1]
			ind.sex <- info[ind_num,2]
			ind.MFC <- info[ind_num,3]
			ind.Fam <- info[ind_num,4]
			#cat("Data:",ind.status,ind.sex,ind.MFC,ind.Fam,sep="\t","\n")
			if(info[ind_num,3]=="M" || info[ind_num,3]=="F"){
				#parentfound
				nparents <- nparents+1
				geno_1 <- as.character(data[locus,colnum])
				geno_1 <- paste(sort(c(substr(geno_1,1,1),substr(geno_1,2,2)))[1],sort(c(substr(geno_1,1,1),substr(geno_1,2,2)))[2],sep="")
				ObservedAllel[substr(geno_1,1,1)] <- ObservedAllel[substr(geno_1,1,1)]+1
				ObservedAllel[substr(geno_1,2,2)] <- ObservedAllel[substr(geno_1,2,2)]+1
				Observed[geno_1] <- Observed[geno_1] +1
				for(ind2_num in which(info[,4]==ind.Fam)){
					if(info[ind2_num,3] != info[ind_num,3] && info[ind2_num,3] != "C"){
						#cat(rownames(info)[ind2_num]," !!!\n")
						colnum_2 <- which(colnames(data)==rownames(info)[ind2_num])
						#cat("Colnum2:",colnum_2,"\n")
						geno_2 <- as.character(data[locus,colnum_2])
						#cat("Geno's:",geno_1,geno_2,"\n")
						geno_2 <- paste(sort(c(substr(geno_2,1,1),substr(geno_2,2,2)))[1],sort(c(substr(geno_2,1,1),substr(geno_2,2,2)))[2],sep="")
						Observedtable[geno_1,geno_2] <- Observedtable[geno_1,geno_2] +1
					}				
				}
			}
			ind_num = ind_num+1
		}
		n.allells=sum(ObservedAllel)
		for(x in 1:length(ObservedAllel)){
			ExpectedAllel[x]=(ObservedAllel[x]) / n.allells
			#here there is a bug: expected != observed / n.allees (this is exected freq)
			ourcat(logger,"AM",names(ObservedAllel)[x],"\t",ObservedAllel[x],"\t",ExpectedAllel[x],"\n",verbose=verbose)
		}
		ourcat(logger,"AM","-----------------------------------------------------------------------\n",verbose=verbose)
		for(x in 1:length(Observed)){
			#cat(x)
			geno_1 <- names(Observed)[x]
			geno_1 <- paste(sort(c(substr(geno_1,1,1),substr(geno_1,2,2)))[1],sort(c(substr(geno_1,1,1),substr(geno_1,2,2)))[2],sep="")
			if(substr(geno_1,1,1) != substr(geno_1,2,2)){
				Expected[x] <- (ExpectedAllel[substr(geno_1,1,1)] * ExpectedAllel[substr(geno_1,2,2)]) * n.allells
			}else{
				Expected[x] <- (ExpectedAllel[substr(geno_1,1,1)] * ExpectedAllel[substr(geno_1,2,2)]) * n.allells /2
			}
			ourcat(logger,"AM","Tests",names(Observed)[x],"\t",Observed[x],"\t",Expected[x],"\n",verbose=verbose)
		}
		cat(" ",colnames(Observedtable),"\n",sep="\t")
		for(x in 1:dim(Observedtable)[1]){
			cat(rownames(Observedtable)[x],rep("\t",x))
			for(y in x:dim(Observedtable)[2]){
				Expectedtable[x,y] <- as.integer((Observed[x]/nparents)*(Observed[y]/nparents)*(nparents/2))
				if(x==y){
					Observedtable[x,y] <- Observedtable[x,y]/2
				}else{
					Expectedtable[x,y] <- Expectedtable[x,y]*2
				}
				cat(Observedtable[x,y],"/",Expectedtable[x,y],"\t",sep="")
			}
			cat("\n")
		}
		#Statistics
		teststat = 0
		dir = 0
		teststat1 = 0
		for(x in 1:length(Expected)){
			geno_1 <- names(Expected)[x]
			a <- substr(geno_1,1,1)
			b <- substr(geno_1,2,2)
			value=0
			if(Expected[x] !=0){
				value = ((Observed[x]-Expected[x])^2/Expected[x])
				teststat <- teststat+value
				if(a==b){
					dir <- 1-(Observed[x]/Expected[x])
				}
			}else{
				teststat <- teststat+0
			}
		}
		ourcat(logger,"AM","Pop TestStat:",teststat,dir,dir*teststat,"\n",verbose=verbose)
		dirHO = 0
		dirHE = 0
		ParentDirection <- NULL
		Pnames <- NULL
		for(x in 1:dim(Expectedtable)[1]){
			for(y in 1:dim(Expectedtable)[2]){
				value <- 0
				if(Expectedtable[x,y] !=0){
					value <- ((Observedtable[x,y]-Expectedtable[x,y])^2/Expectedtable[x,y])	
				}
				if(x==y){
					dirHO = dirHO+value
				}else{
					dirHE = dirHE+value
				}
				ParentDirection <- c(ParentDirection,value)
				Pnames <- c(Pnames,paste(names(Expectedtable)[x],names(Expectedtable)[y]))
				teststat1 <- teststat1+value
			}
		}
		cat(dirHO,dirHE,"\n")
		if((dirHO-dirHE) < 0){
			teststat1 = -teststat1
		}
		ourcat(logger,"AM","Pop TestStat_1:",teststat1,"\n",verbose=verbose)
		pDir <- cbind(pDir,ParentDirection)
		rownames(pDir) <- Pnames
		if(plot){
			op <- par(mfrow = c(2,1))
			DirScores <- c(DirScores,dir)
			PopScores <- c(PopScores,teststat)
			max <- max(as.numeric(PopScores))
			min <- min(as.numeric(PopScores))
			plot(c(1,length(PopScores)),c(min,max),xlab="markers",ylab="Chi^2",type='n')
			lines(PopScores,lwd=2,col=rgb(0.3,0.3,1.0,1.0),type="o")

			ParScores <- c(ParScores,teststat1)		
			max <- max(as.numeric(ParScores))
			min <- min(as.numeric(ParScores))
			plot(c(1,length(ParScores)),c(min,max),xlab="markers",ylab="Chi^2",type='n')
			lines(ParScores,lwd=2,col=rgb(0.3,0.3,1.0,1.0),type="o")
		}
		cat(file=name,paste(rownames(data)[locus],teststat,dir,teststat1,sep="\t"),"\n",append=T)
	}
	list(PopScores,DirScores,ParScores,pDir)
}


init.QQplot <- function(){
	full <- NULL
	for(x in dir()[grep("Chr",dir())]){
		if(!is.na(grep("res",x)==1&&1)){
			cat("Reading",x,"\n")
			data <- read.table(x)
			full <- c(full,data[,2])
		}
	}

}

init.length <- function(){
	setwd("D:\\GBIC\\Lude\\DataDanny")
	order <- as.vector(read.csv("ChipIDOrderInGenotypeFiles.txt",header=FALSE,sep="\n"))
	info <- read.csv("ChipIDToSampleInformation.txt",row.names=1,header=TRUE,sep="\t")
	coln <- c("Chr","Pos",as.vector(order[,1]))
	load("LM.Rdata")
	colnames(LengthMatrix) <- coln
	aaa <- assortedmating(LengthMatrix,info,1,5)
}