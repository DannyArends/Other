#
# zzz.R
# copyright (c) 2011 Danny Arends
# 
# .onAttach is run when the package is loaded with library(qtl)
#

#Global package variables
.PackageEnv <- new.env()

get.PackageEnv <- function(){.PackageEnv}
has <- function(name){ get(name, envir = .PackageEnv) }

.has_d_warnmsg   <- "- D not available, using standard R/C/C++ functionality\n"
.has_d_warning   <- "D not available\n"
.has_d_msg       <- "- D is available\n"

#Package loading
.onAttach <- function(lib, pkg){
  packageStartupMessage("- Loading package\n", appendLF = FALSE)
  .has_d <- TRUE
  
  #Attach the C++ code to the package
  library.dynam("Dcode", pkg, lib)
  
  #Try to attach the compiled D code to the package
  tryCatch( 
    library.dynam("Ddll", pkg, lib),
    error = function(e){
     .has_d <<- FALSE
   })
  assign(".has_d",     .has_d,     envir = .PackageEnv)

  #Inform the user if the D library was found
  if(!has(".has_d")){
    packageStartupMessage(.has_d_warnmsg, appendLF = FALSE)
  }else{
    packageStartupMessage(.has_d_msg, appendLF = FALSE)  
  }
}

# end of zzz.R
