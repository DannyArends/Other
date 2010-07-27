\name{Rexamples-package}
\alias{Rexamples}
\docType{package}
\title{
	Rexamples - Some examples of R functions
}
\description{
	Includes the following functionality:
	General R-C interface
	\itemize{
		\item \code{\link{AddinC}} - Basic example of adding up two integers in C
	}
	Population Simulation
	\itemize{
		\item \code{\link{CreatePopulationHW}} - Population at H/W equilibrium (1/4:1/2:1:4)
		\item \code{\link{CreatePopulation}} - Population not at H/W equilibrium (1/3:1/3:1/3)
		\item \code{\link{BreedRandom}} - simulation of random mating/breeding
		\item \code{\link{BreedAssorted}} - simulation of assorted mating/breeding
	}
	QTL analysis
	\itemize{
		\item \code{\link{analyseQTL}} - main QTL mapping function
		\item \code{\link{mapRF}} - QTL mapping using randomForest algorithm
		\item \code{\link{mapSM}} - QTL mapping using a single marker anova model
	}
	Kinship checking 
	\itemize{
		\item \code{\link{scoreKinship}} - Calculates kinshipscores based on SNP markerdata
		\item \code{\link{parents}} - Finds tripplets of individuals with parents from SNP markerdata
		\item \code{\link{kinshipNetwork}} - Created a .SIF network with kinship relations between individuals
		\item Plot functions:
		\itemize{
			\item \code{\link{plot.parentplot}} - Graphical representation highlighting possible parents of individuals
			\item \code{\link{plot.parentimage}} - Graphical representation highlighting possible parents of individuals
		}
	}
	Assortedmating
	\itemize{
		\item \code{\link{assortedmating}} - Assorted mating algorithm
		\item Plot functions:
		\itemize{
			\item \code{\link{plot.genotypes}} - Graphical representation of the mating between genotypes per marker
			\item \code{\link{plot.popstats}} - Graphical representation of basic population statistics
		}
	}
	
}
\details{
	More detailed information and/or examples are given per function as needed.
}
\author{ 
	Danny Arends \email{Danny.Arends@gmail.com}
	Maintainer: Danny Arends \email{Danny.Arends@gmail.com} 
}
\references{
	\itemize{
	\item Broman, K. W., Wu, H., Sen, 'S. and Churchill, G. A. (2003) R/qtl: QTL mapping in experimental crosses. \emph{Bioinformatics} (\bold{19}) 889–890
	\item Breiman, L. (2001) Random Forests \emph{Machine Learning 45} (\bold{1}) 5-32
	}
}
\keyword{ package }

\seealso{
	\itemize{
		\item \code{\link{AddinC}} - Basic example of adding up two integers in C
		\item \code{\link{analyseQTL}} - QTL mapping function
		\item \code{\link{assortedmating}} - Assorted mating algorithm
		\item \code{\link{scoreKinship}} - Calculates kinshipscores based on SNP markerdata
	}
}
\examples{

}
