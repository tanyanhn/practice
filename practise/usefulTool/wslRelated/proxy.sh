#!/bin/sh

# 注意：这个 ip 地址和我们在 windows 中通过 ipconfig 获取的地址等价
hostip=$(cat /etc/resolv.conf | grep nameserver | awk '{ print $2 }')
# WSL 自身的 ip
wslip=$(hostname -I | awk '{print $1}')
# Windows 上代理软件监听的端口，河对岸为 10808，注意要选中河对岸的 "Allow connections from the LAN"
port=7890

# 注意代理有两种方式，一种基于 http，一种基于 socket5，河对岸是基于 socket5 的
# PROXY_HTTP="socks5://${hostip}:${port}"
PROXY_HTTP="http://${hostip}:${port}" # 如果是基于 http 的代理，则使用该命令

# 开启代理
set_proxy(){
    export http_proxy="${PROXY_HTTP}"
    export HTTP_PROXY="${PROXY_HTTP}"
    
    export https_proxy="${PROXY_HTTP}"
    export HTTPS_proxy="${PROXY_HTTP}"
    
    export ALL_PROXY="${PROXY_SOCKS5}"
    export all_proxy=${PROXY_SOCKS5}
    
    # 配置 git 的代理
    git config --global http.https://github.com.proxy ${PROXY_HTTP}
    git config --global https.https://github.com.proxy ${PROXY_HTTP}
    
    echo "Proxy has been opened."
}

# 关闭代理
unset_proxy(){
    unset http_proxy
    unset HTTP_PROXY
    unset https_proxy
    unset HTTPS_PROXY
    unset ALL_PROXY
    unset all_proxy
    git config --global --unset http.https://github.com.proxy
    git config --global --unset https.https://github.com.proxy
    
    echo "Proxy has been closed."
}

# 测试代理是否开启成功
test_setting(){
    echo "Host IP:" ${hostip}
    echo "WSL IP:" ${wslip}
    echo "Try to connect to Google..."
    resp=$(curl -I -s --connect-timeout 5 -m 5 -w "%{http_code}" -o /dev/null www.google.com)
    if [ ${resp} = 200 ]; then
        echo "Proxy setup succeeded!"
    else
        echo "Proxy setup failed!"
    fi
}

# 根据我们的输入来执行代理的开启、关闭和测试过程
if [ "$1" = "set" ]
then
    set_proxy
elif [ "$1" = "unset" ]
then
    unset_proxy
elif [ "$1" = "test" ]
then
    test_setting
else
    echo "Unsupported arguments."
fi
