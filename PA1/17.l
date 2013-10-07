 
(*(*function determining length of list*) nested comments

over line breaks
 *)
fun length with list = 
  if isNil list then 0 else list + (length(#list))
in
(length "This"@"is"@"a"@"list")
