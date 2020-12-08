FROM rootproject/root:6.20.08-ubuntu20.04
LABEL MAINTAINER Kamil Rakoczy <kamil.rakoczy@student.uj.edu.pl>

RUN apt-get update && apt-get -y install git unzip && rm -rf /var/lib/apt/lists/*

RUN wget -qO- https://sourceforge.net/projects/boost/files/boost/1.58.0/boost_1_58_0.tar.gz | tar -xz
RUN cd boost_1_58_0 && ./bootstrap.sh && ./b2 install --with-regex --with-test --with-program_options --with-filesystem --with-log --with-atomic
WORKDIR /j-pet-framework
RUN groupadd -g 999 jenkins && useradd -r -u 9999 -g jenkins jenkins
USER jenkins
