FROM centos:latest

# Metadata for my own personal sake
LABEL author="Joshua M. Willis" version="1.0.0"

# Basic additions
RUN yum install clang -y
RUN yum install vim -y
RUN yum install cmake -y
RUN yum install git -y
RUN yum install zip -y
RUN yum install curl -y
RUN yum install cscope -y
RUN yum install tree -y

# TOP tools
RUN yum install epel-release -y
RUN yum install htop -y
RUN yum install iftop -y
RUN yum install iotop -y

# Additional tools
# RUN dnf group install "Development Tools" -y
# I had to comment this out because I couldn't allocate enough space on my EC2 instance reliably

RUN yum update -y

# Set-up and source a default user and profile/bashrc
#RUN useradd -m -s /bin/bash dev
#RUN chmod 700 /home/dev
#USER dev
COPY ./.bashrc /root/.bashrc

# Let's add some of our code and automatically compile it.
COPY ./code /root/code

WORKDIR /root/code

CMD ["/bin/bash", "-c",  "source /root/.bashrc"]
