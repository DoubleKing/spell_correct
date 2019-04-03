<?php
/**
 * Socket客户端
 * author: dapiqing
 * email: dapiqing@qq.com
 * time: 19/04/01 下午1:03
 */
error_reporting(E_ALL);
//设置无限请求超时时间
set_time_limit(0);

$ip = '144.34.211.197';
$port = 8089;

//创建socket
if(($socket = socket_create(AF_INET,SOCK_STREAM,SOL_TCP)) < 0) {
    echo "[]";
    exit();
}

//连接socket
if(($result = socket_connect($socket, $ip, $port)) < 0){
    echo "[]";
    exit();
}

$in = $_GET['term'];
$out = '';

//写数据到socket缓存
if(!socket_write($socket, $in, strlen($in))) {
    echo "[]";
    exit();
}
$out = socket_read($socket, 2048);
echo $out;
socket_close($socket);
 
?>
