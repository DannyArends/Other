\name{analyseQTL}
\alias{analyseQTL}
\title{ analyseQTL - simulation / modeling / mapping / permutation of QTL in a population with SNP markers}
\description{
	Function dedicated to the running of simulation / modeling / mapping / permutation of QTL in a population with SNP markers.
	Currently simulating a population at H/W equilibrium (1/4:1/2:1/4)
}
\usage{
	analyseQTL(data=testdata(),datachecking=datacheck,modelselection=modelQTL,mapping=mapQTL,permutation=permQTL)
}

\arguments{
	\item{data}{ Genotypes individuals + single trait }
	\item{datachecking}{ Function performing datachecking }
	\item{modelselection}{ Function performing modelselection }
	\item{mapping}{ Function performing QTL mapping }
	\item{permutation}{ Function performing QTL permutation }
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
		\item \code{\link{mapRF}} - QTL mapping using randomForest algorithm
		\item \code{\link{mapSM}} - QTL mapping using a single marker anova model
	}
}
\examples{
	data <- testdata()
	analyseQTL(data,mapping=mapSM)
	analyseQTL(data,mapping=mapRF)
}
\keyword{ ~kwd1 }
\keyword{ ~kwd2 }
