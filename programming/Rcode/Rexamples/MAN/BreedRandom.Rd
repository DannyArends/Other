\name{BreedRandom}
\alias{BreedRandom}
\title{ BreedRandom - Simulation of random breeding in a population }
\description{
	Simulation of random breeding in a population
}
\usage{
	BreedRandom(population,n.child)
}

\arguments{
	\item{population}{ populationmatrix }
	\item{n.child}{ number of children }
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
	\item \code{\link{BreedAssorted}} - simulation of assorted mating/breeding
	\item \code{\link{scoreKinship}} - Calculates kinshipscores based on SNP markerdata
	}
}
\examples{
	#Create a population at H/W equilibrium
	population <- CreatePopulationHW(300,150)
	
	#Breed randomly a generation (parents)
	population <- BreedRandom(population,50)
	
	#Breed randomly a next generation (parents + children)
	population <- BreedRandom(population,50)
	
	#Breed randomly a next generation (parents + children + grandchildren)
	population <- BreedRandom(population,50)
	
	Bresult1 <- assortedmating(population$data,population$parentlist[[2]],plot=FALSE,verbose=FALSE)
	Bresult2 <- assortedmating(population$data,population$parentlist[[3]],plot=FALSE,verbose=FALSE)
	Bresult3 <- assortedmating(population$data,population$parentlist[[4]],plot=FALSE,verbose=FALSE)
	
	plot.all(Bresult1)	#Plot the results from the first breeding
	plot.all(Bresult2)	#Plot the results from the second breeding
	plot.all(Bresult3)	#Plot the results from the third breeding
}
\keyword{ ~kwd1 }
\keyword{ ~kwd2 }
