let QT_HOME = 'C:/Qt/6.8.0'
let QT_FLAVOUR = 'msvc2022_64'
let QT_PREFIX_PATH = $"($QT_HOME)/($QT_FLAVOUR)"
let SNDFILE_PREFIX_PATH = 'C:/Users/sadguitarius/dev/source/supercollider_build/x64/libsndfile'
let FFTW_PREFIX_PATH = 'C:/Users/sadguitarius/dev/source/supercollider_build/x64/fftw'
let CMAKE_PREFIX_PATH = $"($QT_PREFIX_PATH);($SNDFILE_PREFIX_PATH);($FFTW_PREFIX_PATH)"
let Path = ($env.Path | prepend C:\Qt\6.8.0\msvc2022_64\bin)

module scdev {
  export-env {
    load-env {
      QT_HOME: $QT_HOME
      QT_FLAVOUR: $QT_FLAVOUR
      QT_PREFIX_PATH: $QT_PREFIX_PATH
      QT_VERSION_MAJOR: 6
      SNDFILE_PREFIX_PATH: $SNDFILE_PREFIX_PATH
      FFTW_PREFIX_PATH: $FFTW_PREFIX_PATH
      CMAKE_PREFIX_PATH: $CMAKE_PREFIX_PATH
      SNDFILE_LIBRARY_DIR: `C:/Users/sadguitarius/dev/source/supercollider_build/x64/libsndfile/bin`
      Path: $Path
    }
  }
}
