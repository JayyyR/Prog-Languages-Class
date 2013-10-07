(* 
Please pay no attention to (* 
the man *)
hiding (*
betwixt the (*
comment *)
signs *)
*)
fun countdown with n = if n=1 then (print 1) else (print n) + (countdown (n-1)) in countdown 10 