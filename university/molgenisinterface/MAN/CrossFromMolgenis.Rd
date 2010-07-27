\name{CrossFromMolgenis}
\alias{CrossFromMolgenis}

\title{ CrossFromMolgenis - Create a cross-object from a molgenis database }
\description{
  Helperfunction to create a cross-object from a molgenis database
}
\usage{
	CrossFromMolgenis <- function(DBmarkerID=0, DBtraitID=0, DBpath=NULL, verbose=TRUE)
}

\arguments{
  \item{DBmarkerID}{ Database ID of the matrix with individuals*markers }
  \item{DBtraitID}{ Database ID of the matrix with individuals*traits }
  \item{trait}{ When trait>0, a single trait is retrieved from the database }
  \item{DBpath}{ Path to the molgenis database }
  \item{verbose}{If TRUE, print tracing information}
}
\details{
The library RCurl from bioconductor should be installed to use a molgenis interface.
}
\value{
	Cross object, An object of class \code{cross} from R/QTL with multiple phenotypes suitable for scanone and scanMQM from R/QTL. See \code{\link[qtl]{read.cross}} for details. 
}

\author{ Danny Arends \email{Danny.Arends@gmail.com} ; M.A. Swertz \email{m.a.swertz@rug.nl} ; R.C. Janssen \email{r.c.jansen@rug.nl} }

\note{
The library RCurl should be installed before attempting to use this function. This library can be obtained from bioconductor or omegahat.
\itemize{
	\item \url{http://www.bioconductor.org} or \url{http://www.omegahat.org/RCurl/}
	\item \url{http://www.molgenis.org}
	\item \url{http://www.Xgap.org}
}
If u find anything wrong with the algorithm please notify me at: \email{Danny.Arends@gmail.com}
}

\seealso{ 
\itemize{
	\item \code{\link[qtl]{scanMQM}} - Function called to do single trait analysis
	\item \code{\link[qtl]{scanMQMall}} - Function called to do single trait analysis
	\item \code{\link{run_cluster}} - Automatic QTL analysis PBS clusters
	\item \code{\link{CrossFromMolgenis}} - Function called to retrieve an object of type cross to a molgenis database
	\item \code{\link{ResultsFromMolgenis}} - Function called to retrieve results to a molgenis database
	\item \code{\link{ResultsToMolgenis}} - Function to store results into a molgenis database
}
}
\examples{
	\dontrun{
		cross <- CrossFromMolgenis()		#Make a crossobject from the database
		result <- mqmall(cross)			#Basic execution of scanall
		ResultsToMolgenis(result,"QTL-mqm")	#Store the result from MQM into molgenis database
	}
}
\references{
	\url{http://www.molgenis.org} \& \url{http://www.Xgap.org} \& \url{http://www.omegahat.org/RCurl/}
	\itemize{
		\item Temple Lang D. (2008), R as a Web Client – the RCurl package \emp{Journal of Statistical Software}
		\item Swertz MA, Jansen RC. (2007), Beyond standardization: dynamic software infrastructures for systems biology. \emph{Nat Rev Genet.} \bold{3}, 235--243.
		\item Swertz MA, De Brock EO, Van Hijum SA, De Jong A, Buist G, Baerends RJ, Kok J, Kuipers OP, Jansen RC. (2004), Molecular Genetics Information System (MOLGENIS): alternatives in developing local experimental genomics databases. \emph{Bioinformatics},\bold{13}, 2075--2083.
	}
}
\keyword{ QTL }
\keyword{ Mapping }
\keyword{ Selection }
