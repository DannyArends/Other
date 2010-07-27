#####################################################################
#
# PERMUTATIONanalysis.R
#
# copyright (c) 2009, Danny Arends
# last modified Fep, 2009
# first written Oct, 2009
# 
# Part of the R/qtl package
# Contains: run_cluster
#
######################################################################

######################################################################
#
# run_cluster: main routine to distribute jobs across a cluster of computers
# generateRunfile: Generates a .sh file with job description to be submitted to pbs
# generate_Statement: Wraps a command inside tryCatch using the reporter
# generateQTLfile: Generates a QTL file which is executed (R CMD BATCH <qtlfile>) by a cluster
# generateESTfile: Generates a QTL file to estimate runtime for each item
# DownloadnSave: Saves a Crossobject to the HDD in .RData format for easy loading
# install_libraries: Installs libraries needed on the cluster inside ~/libs
# prepare_cluster: Setup of foldersystem
# est_runtime: Estimates runtime by executing the file produced by generateESTfile
# report/report_status: Reporting back to the molgenis server
#
######################################################################

generateRunfile <- function(job, est,taskID){
	#Generate a runfile to submit to the cluster
	runfile <- paste("~/run",taskID,"/run",job,".sh",sep="")
	cat("#!/bin/sh","\n",sep="",file=runfile)
	#We need just 1 node TODO: use 2 processors and SNOW on a clusterNODE
	cat("#PBS -l nodes=1","\n",sep="",file=runfile,append=T)
	#Our estimate
	cat("#PBS -l walltime=",est,"\n",sep="",file=runfile,append=T)
	#Go to the correct location
	cat(paste("cd $HOME/run",taskID,sep=""),"\n",sep="",file=runfile,append=T)
	#StartRunning
	cat("R CMD BATCH perm",job,".R",sep="",file=runfile,append=T)
	runfile
}

#tryCatch(stop(9), error = function(e) e) Do this for eveything that could fail on the servlets...

Generate_Statement <- function(statement){
	#printing a secured statement (just means we report a 3 if we fail)
	secured <- paste("tryCatch(\n\t",statement,"\t,error =  function(e){report(-1,e$message)}\n)\n",sep="")
	secured
}

generatePERMfile <- function(DBmarkerID = 0, DBtraitID = 0, DBpath = "", job, b_size,Ntraits,name,taskID,nperm,map,method,model){
	#Generate a qtl<#>.R file to do the analysis on
	qtlfile <- paste("~/run",taskID,"/perm",job,".R",sep="")
	#load needed libraries
	cat("library(qtl,lib.loc='~/libs')","\n",sep="",file=qtlfile)
	cat("library(RCurl,lib.loc='~/libs')","\n",sep="",file=qtlfile,append=T)
	cat("library(molgenis,lib.loc='~/libs')","\n",sep="",file=qtlfile,append=T)
	cat("library(snow,lib.loc='~/libs')","\n",sep="",file=qtlfile,append=T)
	#Print our report function
	cat("\nreport <- function(status,text){\n",file=qtlfile,append=T)
	cat("\ttask <- ",taskID,"\n",file=qtlfile,append=T)
	cat("\ttext <- substr(URLencode(text),0,100)\n",file=qtlfile,append=T)
	cat("\tjob <- ",job,"\n",file=qtlfile,append=T)
	cat("\tlink <- paste(\"",DBpath,"/taskreporter?task=\",task,\"&job=\",job,\"&statuscode=\",status,\"&statustext=\",text,sep=\"\")\n",sep="",file=qtlfile,append=T)
	cat("\tgetURL(link)\n",file=qtlfile,append=T)
	cat("\tif(status==-1){\n\t\tcat(\"!!!\",text,\"!!!\")\n\t\tq(\"no\")\n\t}\n",file=qtlfile,append=T)
	cat("}\n\n",file=qtlfile,append=T)
	#Start by sending a message (so we know we're running
	cat("report(2,\"LoadingCrossobject\")\n",file=qtlfile,append=T)
	cat(Generate_Statement(paste("load(\"~/run",taskID,"/cross.RData\")","\n",sep="")),file=qtlfile,append=T)
	cat("report(2,\"FinishedLoading\")\n",file=qtlfile,append=T)
	#Which genotypes do we actually need ? (throw away any remaining)
	if(((job-1)*b_size)+b_size > Ntraits){
		#final batch
		cat(Generate_Statement(paste("cross$pheno <- cross$pheno[",((job-1)*b_size)+1,":",Ntraits,"]","\n",sep="")),file=qtlfile,append=T)
	}else{
		cat(Generate_Statement(paste("cross$pheno <- cross$pheno[",((job-1)*b_size)+1,":",((job-1)*b_size)+b_size,"]","\n",sep="")),file=qtlfile,append=T)
	}
	#Store results
	cat("Thresholds <- NULL\n",file=qtlfile,append=T)
	cat("Names <- NULL\n",file=qtlfile,append=T)
	cat("for(num in 1:nphe(cross)){\n",file=qtlfile,append=T)
	cat(Generate_Statement(paste("bresults <- bootstrap(cross,n.run=",nperm,",pheno.col=num,Funktie=",map,",method='",method,"',model='",model,"',multiC=FALSE,verbose=TRUE)","\n",sep="")),file=qtlfile,append=T)
	cat(Generate_Statement(paste("results <- summary(MQMpermObject(bresults))[,1]","\n",sep="")),file=qtlfile,append=T)
	cat(Generate_Statement(paste("Thresholds <- rbind(Thresholds,results)","\n",sep="")),file=qtlfile,append=T)
	cat(Generate_Statement(paste("Names <- c(Names,substr(colnames(bresults[[1]])[3],5,nchar(colnames(bresults[[1]])[3])))","\n",sep="")),file=qtlfile,append=T)
	cat("}\n",file=qtlfile,append=T)
	cat("rownames(Thresholds) <- Names\n",file=qtlfile,append=T)
	cat("Thresholds\n",file=qtlfile,append=T)
	cat(Generate_Statement(paste("PermToMolgenis(permResults=Thresholds,",(job-1)*b_size,",DBpath='",DBpath,"',name='",name,"')\n",sep="")),file=qtlfile,append=T)
	cat("report(3,\"JobFinished\")\n",file=qtlfile,append=T)
	#Quit
	cat("q(\"no\")","\n",sep="",file=qtlfile,append=T)
}

generateESTfile <- function(DBmarkerID = 0, DBtraitID = 0, DBpath = "",nperm,map,method,model,taskID){
	#Generates a qtlfile to estimate walltime
	qtlfile <- paste("~/run",taskID,"/ESTtime.R",sep="")
	#Print our report function
	cat("\nreport <- function(status,text){\n",file=qtlfile)
	cat("\ttask <- ",taskID,"\n",file=qtlfile,append=T)
	cat("\ttext <- substr(URLencode(text),0,100)\n",file=qtlfile,append=T)
	cat("\tlink <- paste(\"",DBpath,"/taskreporter?task=\",task,\"&job=0&statuscode=\",status,\"&statustext=\",text,sep=\"\")\n",sep="",file=qtlfile,append=T)
	cat("\tgetURL(link)\n",file=qtlfile,append=T)
	cat("\tif(status==-1){\n\t\tcat(\"!!!\",text,\"!!!\")\n\t\t\n\t\tq(\"no\")\n\t}\n",file=qtlfile,append=T)
	cat("}\n\n",file=qtlfile,append=T)
	#load needed libraries	
	cat("library(qtl,lib.loc='~/libs')","\n",sep="",file=qtlfile,append=T)
	cat("library(RCurl,lib.loc='~/libs')","\n",sep="",file=qtlfile,append=T)
	cat("library(molgenis,lib.loc='~/libs')","\n",sep="",file=qtlfile,append=T)
	cat(Generate_Statement(paste("load(\"~/run",taskID,"/cross.RData\")","\n",sep="")),file=qtlfile,append=T)
	cat("cross$pheno <- cross$pheno[1]","\n",sep="",file=qtlfile,append=T)
	cat(Generate_Statement(paste("results <- bootstrap(cross,n.run=",nperm,",Funktie=",map,",method='",method,"',model='",model,"',multiC=FALSE,verbose=TRUE)","\n",sep="")),file=qtlfile,append=T)
	#Quit
	cat("q(\"no\")","\n",sep="",file=qtlfile,append=T)
}

DownloadnSave <- function(DBmarkerID = 0, DBtraitID = 0, DBpath = "",taskID,njobs){
	#Generates a R-script to download all the information and build a cross object
	qtlfile <- paste("~/run",taskID,"/download.R",sep="")
	#Print our report function
	cat("\nreport <- function(status,text){\n",file=qtlfile)
	cat("\ttask <- ",taskID,"\n",file=qtlfile,append=T)
	cat("\ttext <- substr(URLencode(text),0,100)\n",file=qtlfile,append=T)
	cat("\tlink <- paste(\"",DBpath,"/taskreporter?task=\",task,\"&job=0&statuscode=\",status,\"&statustext=\",text,sep=\"\")\n",sep="",file=qtlfile,append=T)
	cat("\tgetURL(link)\n",file=qtlfile,append=T)
	cat("\tif(status==-1){\n\t\tcat(\"!!!\",text,\"!!!\")\n\t\t\n\t\tq(\"no\")\n\t}\n",file=qtlfile,append=T)
	cat("}\n\n",file=qtlfile,append=T)
	#load needed libraries
	cat("library(qtl,lib.loc='~/libs')","\n",sep="",file=qtlfile,append=T)
	cat("library(RCurl,lib.loc='~/libs')","\n",sep="",file=qtlfile,append=T)
	cat("library(molgenis,lib.loc='~/libs')","\n",sep="",file=qtlfile,append=T)
	#Downloading of Cross object (secured)
	cat(Generate_Statement(paste("cross <- CrossFromMolgenis(DBmarkerID=",DBmarkerID,",DBtraitID=",DBtraitID,",DBpath='",DBpath,"')","\n",sep="")),file=qtlfile,append=T)
	cat(Generate_Statement(paste("save(cross,file=\"~/run",taskID,"/cross.RData\")","\n",sep="")),file=qtlfile,append=T)
	cat("q(\"no\")","\n",sep="",file=qtlfile,append=T)
}

install_libraries <- function(){
	cat("Installing libraries\n")
	#Commands to execute to install R-libs
	system("R CMD INSTALL ~/required/qtl_1.12-16.tar.gz --library=~/libs")
	system("R CMD INSTALL ~/required/RCurl_0.91-0.tar.gz --library=~/libs")
	system("R CMD INSTALL ~/required/molgenis_0.01.tar.gz --library=~/libs")
	system("R CMD INSTALL ~/required/snow_0.3-3.tar.gz --library=~/libs")
}

prepare_cluster <- function(taskID){
	cat("Creating directory\n")
	#Create a directory and switch to it (in R and on the shell (so our next R's we'll spawn will not have 2 switch dirs)
	system(paste("mkdir run",taskID,sep=""))
	system(paste("cd run",taskID,sep=""))
	setwd(paste("~/run",taskID,sep=""))
}

est_runtime <- function(njobs,DBmarkerID=0, DBtraitID = 0,ntraits=1, DBpath = "",num_per_run=1,taskID,nperm,map,method,model){
	#Crude estimation of time that it would take a job of num_per_run qtls to finish, we get all the data from molgenis and run 2 qtls profiles
	generateESTfile(DBmarkerID, DBtraitID, DBpath,nperm,map,method,model,taskID)
	#time execution of executing 1 trait
	s <- proc.time()
	system("R CMD BATCH ESTtime.R")
	e <- proc.time()
	#Add 5% for security
	EST <- (num_per_run)*((e[3]-s[3])+10) 
	ESTtime <- sprintf("%02.f:%02.f:%02.f",EST %/% 3600, (EST%%3600) %/% 60, round(EST%%60, digits = 0))
	if(EST >  864000){
		report(dbpath,taskid,0,-1,"JobsTooLong")
	}else{
		ESTtime
	}
}


report <- function(DBpath,task,job,status,text){
	progress <- 0
	text <- substr(URLencode(text),0,100)
	link <- paste(DBpath,"/taskreporter?task=",task,"&job=",job,"&statuscode=",status,"&statustext=",text,"&statusprogress=",progress,sep="")
	getURL(link)
	if(status==-1){
		q("no")
	}
}

run_cluster <- function(name = "permTEST",genotypes = 0 , phenotypes = 0,totalitems=1, njobs=1,dbpath = "",taskid=1,nperm=1000,map="scanone",method="hk",model="normal"){
	#Initializes the cluster, installs R-libraries (could only be done once)
	#Downloads the datafile from molgenis and save it as a .RData
	#Estimated time needed for each run (very crude) (totalitems in run + 25%)
	#--Generate a PERMfile
	#--Generate runfile for cluster
	#--Sends the runfile as a job to the cluster
	genotypes <- as.integer(genotypes)
	phenotypes <- as.integer(phenotypes)
	totalitems <- as.integer(totalitems)
	njobs <- as.integer(njobs)
	taskid <- as.integer(taskid)	
	prepare_cluster(taskid)
	library(qtl,lib.loc='~/libs')
	library(RCurl,lib.loc='~/libs')
	library(molgenis,lib.loc='~/libs')
	est = NULL
	runfile = NULL
	if(totalitems < njobs){
		njobs = totalitems
	}
	nprun <- ceiling(totalitems/njobs)
	cat("# of Traits:",totalitems,"\n# of Jobs",njobs,"# per run",nprun,"\n")
	tryCatch(DownloadnSave(genotypes,phenotypes,DBpath=dbpath,taskid,njobs)
		,error =  function(e){report(dbpath,taskid,0,-1,"Downloadscript")}
	)
	report(dbpath,taskid,0,2,"GeneratedDownload")
	tryCatch(system("R CMD BATCH download.R")
		,error =  function(e){report(dbpath,taskid,0,-1,"DownloadingCross")}
	)
	report(dbpath,taskid,0,2,"FinishedDownloadingDatasets")	
	tryCatch(est <- est_runtime(njobs,genotypes,phenotypes,totalitems,DBpath=dbpath,nprun,taskid,nperm,map,method,model)
		,error =  function(e){report(dbpath,taskid,0,-1,"EstimatingTime")}
	)
	if(is.null(name)) name="qtlTEST"
	cat("Estimated for ",name,". Runtime per job=",est,"\n")
	report(dbpath,taskid,0,2,"EstimatedRuntime")
	#ALL DONE NOW WE CAN GO INTO/run directory and make some calculations
	for(x in 1:njobs){
		cat("Generating: ",x,".1/",njobs,"\n",sep="")
		tryCatch(generatePERMfile(DBmarkerID=genotypes, DBtraitID=phenotypes, DBpath=dbpath, job=x, b_size=nprun,Ntraits=totalitems,name=name,taskid,nperm,map,method,model)
			,error =  function(e){report(dbpath,taskid,x,-1,"GeneratingQTLrunfile")}
		)
		report(dbpath,taskid,0,2,paste("Generated_QTL",x,sep=""))	
		cat("Generating: ",x,".2/",njobs,"\n",sep="")
		tryCatch(runfile <- generateRunfile(x,est,taskid)
			,error =  function(e){report(dbpath,taskid,x,-1,"GeneratingSHrunfile")}
		)
		report(dbpath,taskid,0,2,paste("Generated_SH",x,sep=""))	
		cat("Submitting: ",x,".3/",njobs,":",runfile,"\n",sep="")
		#OLD call to sh to compute on the Sceduler
		tryCatch(system(paste("qsub ",runfile,sep=""))
			,error =  function(e){report(dbpath,taskid,x,-1,paste("SubmissionPBS",e$message,sep=""))}
		)
		report(dbpath,taskid,0,2,paste("Submitted_",x,sep=""))	
		report(dbpath,taskid,x,1,"TaskqueuedbyPBS")
		#system(paste("sh ",runfile,sep=""))
	}
	report(dbpath,taskid,0,3,"PreparationDone")
}