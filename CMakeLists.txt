cmake_minimum_required( VERSION 3.10 )

project( net_io LANGUAGES C )

add_executable( client client.c )
add_executable( select select.c )
add_executable( epoll epoll.c )
add_executable( poll poll.c )
