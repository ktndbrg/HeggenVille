set s [socket 192.168.1.12 8920]
fconfigure $s -buffering line
puts $s "hello, world!"

set input [gets $s]
puts $input

