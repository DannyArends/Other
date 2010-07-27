#####################################################################
#
# PipelineMolgenis.R
#
# copyright (c) 2009, Danny Arends
# last modified Mrt, 2009
# first written Oct, 2009
#
#     This program is free software; you can redistribute it and/or
#     modify it under the terms of the GNU General Public License, as
#     published by the Free Software Foundation; either version 2 of
#     the License, or (at your option) any later version. 
# 
#     This program is distributed in the hope that it will be useful,
#     but without any warranty; without even the implied warranty of
#     merchantability or fitness for a particular purpose.  See the
#     GNU General Public License for more details.
# 
#     A copy of the GNU General Public License is available at
#     http://www.r-project.org/Licenses/
#
# Part of the R/qtl package
# Contains: PipelineMolgenis
#
######################################################################

######################################################################
#
# PipelineMolgenis:
#
######################################################################

PipelineMolgenis <- function(DBmarkerID,DBtraitID,multiC=TRUE,name="MQMResults",DBpath,each=0,n.clusters=2,...){
	cat("------------------------------------------------------------------\n")
	cat("Starting Molgenis <-> MQM <-> Molgenis automated pipeline\n")
	cat("INFO: Molgenisserver:",DBpath,"\n")
	cat("INFO: Genotype info-tableID:",DBmarkerID," (DBmarkerID)\n")
	cat("INFO: Phenotype values-tableID:",DBtraitID," (DBtraitID)\n")
	cat("INFO: Results will be stored in a table named:",name,"\n")	
	cat("------------------------------------------------------------------\n")
	cat("INFO: Starting data retrieval.\n")	
	cat("INFO: Please be patient while all data is retrieved.\n")	
	cat("------------------------------------------------------------------\n")
	start <- proc.time()
	all_data <- CrossFromMolgenis(DBmarkerID,DBtraitID,trait=0,DBpath,verbose=F)
	all_data <- fill.geno(all_data)
	num_traits <- nphe(all_data)
	summary(all_data)
	end <- proc.time()
	cat("------------------------------------------------------------------\n")
	cat("INFO: Data retrieval finished in",round((end-start)[3], digits = 3),"seconds\n")
	cat("------------------------------------------------------------------\n")
	PRE <- (end-start)[3]
	SUM <- 0
	AVG <- 0
	LEFT <- 0
	#TEST FOR SNOW CAPABILITIES
	if(("snow" %in% installed.packages()[1:dim(installed.packages())[1]]) && multiC){
		start <- proc.time()
		cat("INFO: Library snow found using ",n.clusters," Cores/CPU's/PC's for calculation.\n")
		outcome <- NULL
		library(snow)
		cl <- makeCluster(n.clusters)
		clusterEvalQ(cl, library(qtl))
		outcome <- parLapply(cl,1:num_traits, snowCore,each=each,all_data=all_data,name=name,DBpath=DBpath)
		stopCluster(cl)
		end <- proc.time()
		SUM <- SUM + (end-start)[3]
		AVG <- SUM/num_traits
		cat("------------------------------------------------------------------\n")		
		cat("INFO: Elapsed time:",(SUM+PRE%/%3600),":",(SUM+PRE%%3600)%/%60,":",round(SUM+PRE%%60, digits=0),"(Hour:Min:Sec) (",round(PRE, digits=3),",",round(SUM, digits=3),")\n")		
		cat("INFO: Average time per trait:",round(AVG, digits=3),"seconds\n")
		cat("------------------------------------------------------------------\n")	
	}else{
		for(x in 1:num_traits){
			start <- proc.time()
			cat("\n\n------------------------------------------------------------------\n")
			cat("INFO: Starting analysis of trait (",x,"/",num_traits,")",names(all_data$pheno)[x],"\n")
			cat("------------------------------------------------------------------\n")
			cat("INFO: Scanning for QTL's\n")
			cat("------------------------------------------------------------------\n")
			if(each>1){
				cof <- MQMCofactorsEach(all_data,each)
				result <- scanMQM(all_data,cof,pheno.col=x,plot=T,verbose=F,...)
			}else{
				result <- scanMQM(all_data,pheno.col=x,plot=T,verbose=F,...)
			}
			cat("------------------------------------------------------------------\n")			
			cat("INFO: Finished scanning for QTL's\n")	
			cat("INFO: Uploading calculated QTL's to Molgenis\n")
			cat("------------------------------------------------------------------\n")
				ResultsToMolgenis(result, name,(x-1),DBpath, verbose=F)
			end <- proc.time()		
			SUM <- SUM + (end-start)[3]
			AVG <- SUM/x
			LEFT <- AVG*(num_traits-x)
			cat("------------------------------------------------------------------\n")
			cat("INFO: Finished uploading of QTL's\n")
			cat("------------------------------------------------------------------\n")
			cat("INFO: Calculation of trait",x,"took:",round((end-start)[3], digits=3),"seconds\n")
			cat("INFO: Elapsed time:",(SUM+PRE%/%3600),":",(SUM+PRE%%3600)%/%60,":",round(SUM+PRE%%60, digits=0),"(Hour:Min:Sec) (",round(PRE, digits=3),",",round(SUM, digits=3),")\n")
			cat("INFO: Average time per trait:",round(AVG, digits=3),"seconds\n")
			cat("INFO: Estimated time left:",LEFT%/%3600,":",(LEFT%%3600)%/%60,":",round(LEFT%%60,digits=0),"(Hour:Min:Sec)\n")
			cat("------------------------------------------------------------------\n")	
		}
	}
}

# end of pipelineMolgenis.R