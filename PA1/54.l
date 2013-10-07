
fun help with l1=
	if isNil #l1 then l1
	else let l1=#l1 in (help l1)
in 
fun or with l2=
	if isNil #l2 then Nil
	else !l2@(or l2)
in
fun revers with l=
	if isNil #l then l
	else let l3=(help l) in
	     let l4=(or l) in
	     l3@(revers l4)
in (revers 1@2@3@4)