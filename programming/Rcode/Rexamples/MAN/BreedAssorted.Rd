\name{BreedAssorted}
\alias{BreedAssorted}
\title{ BreedAssorted - Simulation of assorted breeding in a population }
\description{
	Simulation of assorted breeding in a population between user defined markers using genetic distance measurements
	calculated by the \link{scoreKinship} function
}
\usage{
	BreedAssorted(population,n.child,start,stop,\dots)
}

\arguments{
	\item{population}{ populationmatrix }
	\item{n.child}{ number of children }
	\item{start}{ Assorted mating selects on similairity from the start marker }
	\item{stop}{ Assorted mating selects on similairity to the stop marker }
	\item{\dots}{ Parameters passed to the \code{\link{scoreKinship}} function }
}
\details{

}
\value{

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
		\item \code{\link{scoreKinship}} - Calculates kinshipscores based on SNP markerdata
	}
}
\examples{
	#Create a population at H/W equilibrium
	population <- CreatePopulationHW(300,150)
	
	#Breed assorted (selection between marker:100 and 110) a generation (parents)
	population <- BreedAssorted(population,50,100,110,plot=FALSE)
	
	#Breed assorted (selection between marker:100 and 120) a next generation (parents + children)
	population <- BreedAssorted(population,50,100,120,plot=FALSE)
	
	#Breed assorted (selection between marker:20 and 30) a next generation (parents + children + grandchildren)
	population <- BreedAssorted(population,50,20,30,plot=FALSE)
	
	Bresult1 <- assortedmating(population$data,population$parentlist[[2]],plot=FALSE,verbose=FALSE)
	Bresult2 <- assortedmating(population$data,population$parentlist[[3]],plot=FALSE,verbose=FALSE)
	Bresult3 <- assortedmating(population$data,population$parentlist[[4]],plot=FALSE,verbose=FALSE)
	
	plot.all(Bresult1)	#Plot the results from the first breeding
	plot.all(Bresult2)	#Plot the results from the second breeding
	plot.all(Bresult3)	#Plot the results from the third breeding
}
\keyword{ ~kwd1 }
\keyword{ ~kwd2 }
