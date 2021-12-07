FROM centos:latest

# Metadata for my own personal sake
LABEL author="Joshua M. Willis" version="1.0.0"

RUN yum update -y
RUN yum install clang -y
RUN yum install vim -y
RUN yum install cmake -y
RUN yum install git -y
RUN yum install zip -y
RUN yum install curl -y

# TOP tools
RUN yum install epel-release -y
RUN yum install htop -y
RUN yum install iftop -y
RUN yum install iotop -y

# Additional tools
RUN yum install cscope -y
RUN yum install tree -y

RUN dnf group install "Development Tools" -y

RUN yum update -y

# Set-up and source a default user and profile/bashrc
RUN useradd -m -s /bin/bash dev
RUN chmod 700 /home/dev
USER dev
WORKDIR /home/dev

# Let's add some of our code and automatically compile it.
COPY ./code $HOME
#RUN clang++ /home/code/*.cpp -o /home/a.out


