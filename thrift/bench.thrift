namespace cpp bench

service Database {
   oneway void get(1:binary data, 2:binary ret),
   binary sync_get(1:binary data),
}
