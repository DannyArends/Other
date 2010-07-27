\name{molgenis-package}
\alias{molgenis}
\docType{package}
\title{
	Interface between molgenis & r/qtl
}
\description{
	Interface between molgenis & r/qtl
}
\details{
	\tabular{ll}{
	Package: \tab molgenis\cr
	Version: \tab 0.01\cr
	Date: \tab 25th May 2009\cr
	Depends: \tab R (>= 1.8.0), qtl\cr
	License: \tab GPL version 3 or later\cr
	LazyLoad: \tab yes\cr
	LazyData: \tab yes\cr
	}

	Index:
	\preformatted{
	run_cluster		run_cluster - Automated QTL analysis PBS clusters
	CrossFromMolgenis       CrossFromMolgenis - Helperfunction to create a cross-object from a molgenis database
	ResultsFromMolgenis     ResultsFromMolgenis - Helperfunction to retrieve results from a molgenis database
	ResultsToMolgenis       ResultsToMolgenis - Helperfunction to store results into a molgenis database
	DownloadnSave           DownloadnSave - R/qtl analysis on a PBS cluster
	est_runtime             est_runtime - Estimates runtime by executing the file produced by generateESTfile
	generateESTfile         generateESTfile - Generates a QTL file to estimate runtime for each item
	generateQTLfile         generateQTLfile - Generates a QTL file
	generateRUNfile         generateRUNfile - Generates a .sh file with job description to be submitted to PBS
	molgenis                Interface between molgenis & r/qtl
	prepare_cluster         prepare_cluster - Setup of foldersystem
	}
	\itemize{
		\item 1A: Data retrieval from a molgenis database 
		\item 1B: Formatting into a \code{cross} object. See \code{\link[qtl]{read.cross}} for details. 
		\item 2A.1: MQM QTL Model selection, with specified cofactors
		\item 2A.2: MQM QTL mapping using the selected model
		\item 2B: Storage of QTLmap into the database
	}
}
\author{
Danny Arends \email{Danny.Arends@gmail.com} ; M.A. Swertz \email{m.a.swertz@rug.nl}

Maintainer: Danny Arends \email{Danny.Arends@gmail.com}
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
~~ Optionally other standard keywords, one per line, from file KEYWORDS in ~~
~~ the R documentation directory ~~
\keyword{ package }

\seealso{
	\itemize{
	\item \code{\link[qtl]{scanone}} - Function called to do single trait QTL analysis
	\item \code{\link[qtl]{scanall}} - Function called to do QTL analysis on multiple batched traits
	\item \code{\link[qtl]{mqmall}} - Function called to do mqmQTL analysis on multiple batched traits
	\item \code{\link{prepare_cluster}} - Setup of foldersystem
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
