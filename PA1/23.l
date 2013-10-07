fun cat with l1, l2 =
	if isNil l1 then l2 else
	!l1@(cat #l1 l2)


let f = lambda n. if n=0 then 1 else n*(f(n-1)) in
		(f 5) 
