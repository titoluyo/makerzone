print("Iniciando conexion")
conn=net.createConnection(net.TCP, false) 
conn:on("sent", function(conn, strresult) print("Enviado:",strresult) end)
conn:on("disconnection", function(conn, strresult) print("disconnection:",strresult) end)
conn:on("connection", function(conn, strresult) print("connection:",strresult) end)

conn:on("receive", function(conn, pl) print(pl) end)
conn:dns("checkip.dyndns.org",function(conn,ip) 
    print(ip) 
    conn:connect(80,ip)
    tmr.delay(1000000)
    conn:send("GET / HTTP/1.1\r\nHost: checkip.dyndns.org\r\n"
        .."Connection: keep-alive\r\nAccept: */*\r\n\r\n")
end)