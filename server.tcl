set listenSocket [socket -server Connected 8920]

proc Connected {newSock addr port} {
    puts "Connection from $newSock from $addr at $port"
    fconfigure $newSock -buffering line
    set input [gets $newSock]
    puts $input
    puts $newSock $input
    exit
}

vwait forever
