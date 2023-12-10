cargo build

rm /workspaces/server/lib/libskyfire_rs.so
cp  ./target/debug/libskyfire_rs.so /workspaces/server/lib