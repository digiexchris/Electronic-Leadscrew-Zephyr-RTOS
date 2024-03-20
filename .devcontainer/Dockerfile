ARG VARIANT=ubuntu-22.04
FROM mcr.microsoft.com/devcontainers/cpp:${VARIANT}
LABEL Description="ELSF Build environment clang 14"



RUN apt-get update && apt-get -y --no-install-recommends install \
    build-essential \
    clang \
    clangd \
    lld \
    cmake \
    gdb \
    wget \
    git \
    ninja-build \
    python3 \
    gperf \
    ccache dfu-util device-tree-compiler wget \
    python3-dev python3-pip python3-venv python3-setuptools python3-tk python3-wheel xz-utils file \
    make gcc gcc-multilib g++-multilib libsdl2-dev libmagic1 \
    llvm-14 llvm-14-tools curl clang-format-14 ca-certificates openssl ssh libc++-dev libc++abi-dev 

ENV PIP_ROOT_USER_ACTION=ignore
# Make sure we use the virtualenv:
ENV PATH="/root/venv/bin:/usr/bin:$PATH"
RUN which git
RUN cd /root/ && pip3 install west && \
west init /root/zephyrproject && \
cd /root/zephyrproject && \
west update && west zephyr-export && \
 pip3 install -r /root/zephyrproject/zephyr/scripts/requirements.txt

RUN wget https://github.com/zephyrproject-rtos/sdk-ng/releases/download/v0.16.5-1/zephyr-sdk-0.16.5-1_linux-x86_64.tar.xz && \
wget -O - https://github.com/zephyrproject-rtos/sdk-ng/releases/download/v0.16.5-1/sha256.sum | shasum --check --ignore-missing && \
tar xvf zephyr-sdk-0.16.5-1_linux-x86_64.tar.xz && cd zephyr-sdk-0.16.5-1 && ./setup.sh

RUN cp /root/zephyr-sdk-0.16.5-1/sysroots/x86_64-pokysdk-linux/usr/share/openocd/contrib/60-openocd.rules /etc/udev/rules.d

#RUN COPY --chown=vscode:vscode . .

RUN update-alternatives --install /usr/bin/llvm-cov llvm-cov /usr/bin/llvm-cov-14 100
RUN update-alternatives --install /usr/bin/clang-format clang-format /usr/bin/clang-format-14 100
RUN update-alternatives --install /usr/bin/llvm-profdata llvm-profdata /usr/bin/llvm-profdata-14 100
RUN echo 'vscode:vscode!' | chpasswd

# Configure SSHD.
# SSH login fix. Otherwise user is kicked off after login
#RUN sed 's@session\s*required\s*pam_loginuid.so@session optional pam_loginuid.so@g' -i /etc/pam.d/sshd
#RUN mkdir /var/run/sshd
#RUN bash -c 'install -m755 <(printf "#!/bin/sh\nexit 0") /usr/sbin/policy-rc.d'
#RUN ex +'%s/^#\zeListenAddress/\1/g' -scwq /etc/ssh/sshd_config
#RUN ex +'%s/^#\zeHostKey .*ssh_host_.*_key/\1/g' -scwq /etc/ssh/sshd_config
#RUN RUNLEVEL=1 dpkg-reconfigure openssh-server
#RUN ssh-keygen -A -v
RUN update-rc.d ssh defaults

# Configure sudo.
RUN ex +"%s/^%sudo.*$/%sudo ALL=(ALL:ALL) NOPASSWD:ALL/g" -scwq! /etc/sudoers

EXPOSE 22
