FROM ubuntu:xenial
LABEL MAINTAINER Kamil Rakoczy <kamil.rakoczy@student.uj.edu.pl>
RUN apt-get update \
  && apt-get -y install \
  ccache \
  cmake \
  g++ \
  gcc \
  gfortran \
  git \
  libgif-dev \
  libgsl0-dev \
  libjpeg-dev \
  libpq-dev \
  libpythia8-dev \
  libtbb-dev \
  libtiff-dev \
  libx11-dev \
  libxext-dev \
  libxft-dev \
  libxml2-dev \
  libxpm-dev \
  locales \
  lsb-release \
  make \
  python \
  python-dev \
  sudo \
  doxygen \
  libfftw3-3 \
  libfftw3-dev \
  file \
  wget \
  apt-transport-https \
  man-db \
  mesa-utils \
  unzip \
  freeglut3-dev \
  graphviz \
  && localedef -i en_US -f UTF-8 en_US.UTF-8

RUN rm -rf /var/lib/apt/lists/*
RUN mkdir -p /framework-dependencies
RUN mkdir -p /framework-dependencies/lib
RUN mkdir -p /framework-dependencies/include
RUN wget https://sourceforge.net/projects/boost/files/boost/1.58.0/boost_1_58_0.tar.gz -P /framework-dependencies
RUN tar xvxf /framework-dependencies/boost_1_58_0.tar.gz
RUN cd /boost_1_58_0 && ./bootstrap.sh 
RUN cd /boost_1_58_0 && ./b2 install --prefix=/framework-dependencies --with-regex --with-test --with-program_options --with-filesystem --with-log
RUN wget https://root.cern.ch/download/root_v6.08.06.source.tar.gz
RUN tar xvzf root_v6.08.06.source.tar.gz
RUN mkdir -p root-system
RUN mkdir -p root-system/etc
RUN cd root-6.08.06/build && cmake -Dbuiltin_fftw3=ON -Dbuiltin_ftgl=ON -Dfail-on-missing=ON -Dgviz=OFF -Dbonjour=OFF -Dkrb5=OFF -Dcastor=OFF -Drfio=OFF -Dmysql=OFF -Doracle=OFF -Dodbc=OFF -Dsqlite=OFF -Dpythia6=OFF -Dbuiltin_xrootd=ON -Dgfal=OFF -Ddcache=OFF -Dldap=OFF -Dchirp=OFF -Dhdfs=OFF -Dbuiltin_davix=ON -DCMAKE_INSTALL_PREFIX=/root-system --build .. && make && make install
WORKDIR j-pet-framework
COPY docker-entrypoint.sh /usr/local/bin/
RUN chmod 777 /usr/local/bin/docker-entrypoint.sh \
  && ln -s /usr/local/bin/docker-entrypoint.sh / && ln -s /usr/local/bin/docker-entrypoint.sh /j-pet-framework
ENTRYPOINT [ "bash", "-c", "docker-entrypoint.sh" ]
