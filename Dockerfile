FROM gcc:13.2.0 AS build

COPY ./main.cpp /main.cpp

COPY ./app/botan-3 /usr/local/include/botan-3
COPY ./app/libbotan-3.so /usr/local/lib/libbotan-3.so
COPY ./app/libbotan-3.so /usr/local/lib/libbotan-3.so.5

# Very important, otherwise the botan-3 libraries will not be found
RUN ldconfig
 
RUN set -xe; \
	g++ \
	-std=c++20 \
	-Wall -Wextra \
	-fPIC -pie \
	-I/usr/local/include/botan-3/ \
	-lbotan-3 \
	-o main main.cpp -v

# Sample input file
# Commented because we don't want it packed inside the unikernel binary
#RUN echo "Hello, world!" > input.in

FROM scratch

COPY --from=build /usr/local/lib/libbotan-3.so.5 /usr/local/lib/libbotan-3.so.5
COPY --from=build /usr/local/lib64/libstdc++.so.6 /usr/local/lib64/libstdc++.so.6
COPY --from=build /lib/x86_64-linux-gnu/libm.so.6 /lib/x86_64-linux-gnu/libm.so.6
COPY --from=build /lib/x86_64-linux-gnu/libc.so.6 /lib/x86_64-linux-gnu/libc.so.6
COPY --from=build /usr/local/lib64/libgcc_s.so.1 /usr/local/lib64/libgcc_s.so.1
COPY --from=build /lib64/ld-linux-x86-64.so.2 /lib64/ld-linux-x86-64.so.2
COPY --from=build /etc/ld.so.cache /etc/ld.so.cache

COPY --from=build /main /main

# Sample input file copy
# Commented because we don't want it packed inside the unikernel binary
#COPY --from=build input.in /input.in
