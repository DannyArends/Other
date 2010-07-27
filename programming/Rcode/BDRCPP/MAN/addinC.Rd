\name{addinC}
\alias{addinC}
\title{ addinC - Basic example of adding up two integers in C }
\description{
	Basic example of adding up two integers in C
}
\usage{
	addinC(a, b, verbose = TRUE)
}

\arguments{
  \item{a}{ Integer to add up with b }
  \item{b}{ Integer to add up with a }
  \item{verbose}{ Should we print basic information when in C}
}
\details{
  Provided upon request
}
\value{
	Sum of a and b
}
\references{ 
  None yet
}
\author{ 
	Danny Arends \email{Danny.Arends@gmail.com}
	Maintainer: Danny Arends \email{Danny.Arends@gmail.com} 
}
\note{
  Using SEXP
}
\seealso{
  http://www.biostat.jhsph.edu/~bcaffo/statcomp/files/dotCall.pdf
}
\examples{
result <- addinC(5,10)
result

result <- addinC(27,5)
result == (27+5)
}
