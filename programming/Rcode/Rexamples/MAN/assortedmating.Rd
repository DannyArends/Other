\name{assortedmating}
\alias{assortedmating}
\title{ assortedmating - Calculates from SNP genotyped parents and children mendelian seggregation parameters and Outbreading coefficients }
\description{
	Calculates from SNP genotyped parents and children mendelian seggregation parameters and Outbreading coefficients.
	As a check for the assorted mating theory:
	Some genotypes will not be present in the population, or there could be a bias towards a certain allels
	Some genotypes select eachother for breading 
}
\usage{
	assortedmating(matrix, info,start=1,number=nrow(matrix)-start,plot=TRUE,verbose=TRUE,logger=FALSE)
}

\arguments{
  \item{matrix}{ Matrix with at [col,row] [individual,SNPmarker[0,1,2]] }
  \item{info}{ parent child relations (c(individualID,P1ID,P2ID) for children, where PxID's are individualID columns in the matrix parameter }
  \item{start}{ At which marker should we start }
  \item{number}{ How many marker should we analyse from the start }
  \item{plot}{ Plot during analysis ? }
  \item{verbose}{ Text output during analysis ? }
  \item{logger}{ Text output storage to file during analysis ? }
}
\details{
	Plots a graph with several teststatistics about parent populations
}
\value{
	A list with two items:
	
	\code{Matrix} - "PopulationChi2","Inbreading","PopulationInbreading","MatingChi2"
	
	\code{Matrix} - Deviation from expected matign genotypefrequenties after randommating
}
\references{ 
	
}
\author{ 
	Danny Arends \email{Danny.Arends@gmail.com}
	Maintainer: Danny Arends \email{Danny.Arends@gmail.com} 
}
\note{

}
\seealso{
\itemize{
	\item \code{\link{CreatePopulationHW}} - Population at H/W equilibrium (1/4:1/2:1:4)
	\item \code{\link{CreatePopulation}} - Population not at H/W equilibrium (1/3:1/3:1/3)
	\item \code{\link{BreedRandom}} - simulation of random mating/breeding
	\item \code{\link{BreedAssorted}} - simulation of assorted mating/breeding
}
}
\examples{
	#Create a population at H/W equilibrium
	populationHW <- CreatePopulationHW(300,150)

	#Create a population not at H/W equilibrium
	populationN <- CreatePopulation(300,150)	
	
	#Breed randomly a generation (parents)
	popHWran <- BreedRandom(populationHW,50)
	
	#Breed assorted between marker 50 and 75 a next generation (parents)
	popHWass <- BreedAssorted(populationHW,50,50,75,plot=FALSE)
	
	#Breed randomly a generation (parents)
	popNran <- BreedRandom(populationN,50)
	
	#Breed assorted between marker 50 and 75a next generation (parents)
	popNass <- BreedAssorted(populationN,50,50,75,plot=FALSE)
	

	BresHWran <- assortedmating(popHWran$data,popHWran$parentlist[[2]],plot=FALSE,verbose=FALSE)
	BresHWass <- assortedmating(popHWass$data,popHWass$parentlist[[2]],plot=FALSE,verbose=FALSE)
	BresNran <- assortedmating(popNran$data,popNran$parentlist[[2]],plot=FALSE,verbose=FALSE)
	BresNass <- assortedmating(popNass$data,popNass$parentlist[[2]],plot=FALSE,verbose=FALSE)
	
	plot.all(BresHWran)	#Plot the results from the first breeding
	plot.all(BresHWass)	#Plot the results from the second breeding
	plot.all(BresNran)	#Plot the results from the third breeding
	plot.all(BresNass)	#Plot the results from the third breeding
}

\keyword{ ~kwd1 }
\keyword{ ~kwd2 }
