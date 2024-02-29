.data
	extern trueFuncPtr : qword
.code
	callTrueFuncPtrASM proc
		jmp qword ptr [trueFuncPtr]
	callTrueFuncPtrASM endp
end