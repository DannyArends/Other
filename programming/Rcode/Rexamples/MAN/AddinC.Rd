\name{AddinC}
\alias{AddinC}
\title{ AddinC - Basic example of adding up two integers in C }
\description{
	Basic example of adding up two integers in C
}
\usage{
	AddinC(a, b, verbose = TRUE)
}

\arguments{
  \item{a}{ Integer to add up with b }
  \item{b}{ Integer to add up with a }
  \item{verbose}{ Should we print basic information when in C}
}
\details{

}
\value{
	Sum of a and b
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

}
\examples{
result <- AddinC(5,10)
result

result <- AddinC(27,5,verbose=FALSE)
result == (27+5)
}

\keyword{ ~kwd1 }
\keyword{ ~kwd2 }
