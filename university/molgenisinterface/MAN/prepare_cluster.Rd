\name{prepare_cluster}
\alias{prepare_cluster}

\title{ prepare_cluster - Setup of foldersystem }
\description{
  Setup of foldersystem
}
\usage{
prepare_cluster <- function(taskID)
}

\arguments{
  \item{taskID}{ Which taskID is associated with this job }
}

\details{
	These dependencies must be copied to a PBS server with the following packages in ~/required/<libname>.tar.gz:
	\itemize{
	\item	runCluster.R (inside the molgenis package)
	\item	RCurl (needs a working link to Curl.dll)
	\item	molgenis
	\item	R/qtl
	\item	(optional) SNOW
	}
}

\value{
	No return value
}

\author{ Danny Arends \email{Danny.Arends@gmail.com} ; M.A. Swertz \email{m.a.swertz@rug.nl} ; R.C. Janssen \email{r.c.jansen@rug.nl} }

\note{
The library RCurl,molgenis and R/qtl should be installed before attempting to use this function. This library can be obtained from bioconductor or omegahat.
\itemize{
	\item \url{http://www.bioconductor.org} or \url{http://www.omegahat.org/RCurl/}
	\item \url{http://www.molgenis.org}
	\item \url{http://www.Xgap.org}
	\item \url{http://www.rqtl.org}	
}
If u find anything wrong with the algorithm please notify me at: \email{Danny.Arends@gmail.com}
}

\seealso{ 
\itemize{
	\item \code{\link[qtl]{scanall}} - Function called to do batched QTL trait analysis
	\item \code{\link[qtl]{mqmall}} - Function called to do batched mqm QTL trait analysis
	\item \code{\link[qtl]{cimall}} - Function called to do batched cim QTL trait analysis
	\item \code{\link{DownloadnSave}} - R/qtl analysis on a PBS cluster
	\item \code{\link{generateESTfile}} - Generates a QTL file to estimate runtime for each item
	\item \code{\link{est_runtime}} - Estimates runtime by executing the file produced by generateESTfile
	\item \code{\link{generateQTLfile}} - Generates a QTL file
	\item \code{\link{generateRUNfile}} - Generates a .sh file with job description to be submitted to PBS
	\item \code{\link{run_cluster}} - Automated QTL analysis PBS clusters
	\item \code{\link{CrossFromMolgenis}} - Function called to retrieve an object of type cross to a molgenis database
	\item \code{\link{ResultsFromMolgenis}} - Function called to retrieve results to a molgenis database
	\item \code{\link{ResultsToMolgenis}} - Helperfunction to store results into a molgenis database
}
}
\examples{

}
\references{
	\url{http://www.molgenis.org} \& \url{http://www.Xgap.org} \& \url{http://www.omegahat.org/RCurl/} \& \url{http://www.rqtl.org}	
	\itemize{
		\item Temple Lang D. (2008), R as a Web Client – the RCurl package \emp{Journal of Statistical Software}
		\item Swertz MA, Jansen RC. (2007), Beyond standardization: dynamic software infrastructures for systems biology. \emph{Nat Rev Genet.} \bold{3}, 235--243.
		\item Swertz MA, De Brock EO, Van Hijum SA, De Jong A, Buist G, Baerends RJ, Kok J, Kuipers OP, Jansen RC. (2004), Molecular Genetics Information System (MOLGENIS): alternatives in developing local experimental genomics databases. \emph{Bioinformatics},\bold{13}, 2075--2083.
		\item Jansen RC, (2007) Quantitative trait loci in inbred lines. Chapter 18 of \emph{Handbook of Stat. Genetics} 3rd edition. John Wiley & Sons, Ltd.
		\item Tierney, L., Rossini, A., Li, N., and Sevcikova, H. (2004), The snow Package: Simple Network of Workstations. Version 0.2-1. 	
		\item Rossini, A., Tierney, L., and Li, N. (2003), Simple parallel statistical computing.  \emph{R. UW Biostatistics working paper series} University of Washington. \bold{193}
		\item Jansen RC, Nap JP (2001), Genetical genomics: the added value from segregation. \emph{Trends in Genetics}, \bold{17}, 388--391.
		\item Jansen RC, Stam P (1994), High resolution of quantitative traits into multiple loci via interval mapping. \emph{Genetics}, \bold{136}, 1447--1455.
		\item Churchill, G. A. and Doerge, R. W. (1994) Empirical threshold values for quantitative trait mapping. \emph{Genetics} \bold{138}, 963--971.
		\item Jansen RC (1993), Interval mapping of multiple quantitative trait loci. \emph{Genetics}, \bold{135}, 205--211.
		\item Dempster, A. P., Laird, N. M. and Rubin, D. B. (1977) Maximum likelihood from incomplete data via the EM algorithm.  \emph{J. Roy. Statist. Soc.} B, \bold{39}, 1--38.
	}
}
% Add one or more standard keywords, see file 'KEYWORDS' in the
% R documentation directory.
\keyword{ QTL }
\keyword{ Mapping }
\keyword{ Selection }
