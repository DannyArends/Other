\name{callD}
\alias{callD}
\title{callD - Example function that calls the code }
\description{
	Example function that calls the code
}
\usage{
callD(verbose = FALSE)
}

\arguments{
  \item{verbose}{ Be verbose. }
}
\details{
  This function uses a call into a shared object produced by using the D programming language.
  When it is unable to build the shared object, it detects the missing DLL and is able to fall 
  back to R / C / C++ code.
}
\value{
  None
}

\author{ 
	Danny Arends \email{Danny.Arends@gmail.com}\cr
	Maintainer: Danny Arends \email{Danny.Arends@gmail.com} 
}

\examples{
  require(Dcode)
  result <- callD()
}

\keyword{methods}
