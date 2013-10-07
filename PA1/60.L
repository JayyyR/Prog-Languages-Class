fun printp with x=
let f=printp x in
(printp 5)


fun cat with x,l=
if isNil #x then x@l else !x@(cat #x l) in
(cat 1@2@3 4@5)