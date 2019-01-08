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
  && localedef -i en_US -f UTF-8 en_US.UTF-8

RUN apt-get -y install \
  unzip

RUN DEBIAN_FRONTEND=noninteractive apt-get purge -y gcc-5 g++-5
RUN DEBIAN_FRONTEND=noninteractive apt-get -y install g++-4.9 gcc-4.9
RUN update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-4.9 10 
RUN update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-4.9 10 
RUN update-alternatives --set gcc /usr/bin/gcc-4.9 
RUN update-alternatives --set g++ /usr/bin/g++-4.9

RUN rm -rf /var/lib/apt/lists/*
RUN mkdir -p /framework-dependencies
RUN mkdir -p /framework-dependencies/lib
RUN mkdir -p /framework-dependencies/include
RUN wget https://sourceforge.net/projects/boost/files/boost/1.58.0/boost_1_58_0.tar.gz -P /framework-dependencies
RUN tar xvxf /framework-dependencies/boost_1_58_0.tar.gz
RUN cd /boost_1_58_0 && ./bootstrap.sh 
RUN cd /boost_1_58_0 && ./b2 install --prefix=/framework-dependencies --with-regex --with-test --with-program_options --with-filesystem --with-log
RUN wget https://root.cern.ch/download/root_v5.34.26.source.tar.gz
RUN tar xvzf root_v5.34.26.source.tar.gz
RUN mkdir -p root-system
RUN mkdir -p root-system/etc
RUN cd root && ./configure --prefix=/root-system --etcdir=/root-system/etc --enable-builtin-freetype --disable-mathmore --enable-opengl --with-x11-libdir=/usr/lib/x86_64-linux-gnu --with-xpm-libdir=/usr/lib/x86_64-linux-gnu --with-xft-libdir=/usr/lib/x86_64-linux-gnu --with-xext-libdir=/usr/lib/x86_64-linux-gnu
RUN cd root && make
RUN cd root && make install
RUN ln -sfn /usr/bin/g++ /usr/bin/c++
RUN ln -sfn /usr/bin/gcc /usr/bin/cc
WORKDIR j-pet-framework
COPY docker-entrypoint.sh /usr/local/bin/
RUN chmod 777 /usr/local/bin/docker-entrypoint.sh \
  && ln -s /usr/local/bin/docker-entrypoint.sh / && ln -s /usr/local/bin/docker-entrypoint.sh /j-pet-framework
ENTRYPOINT [ "bash", "-c", "docker-entrypoint.sh" ]
