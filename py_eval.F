	subroutine py_eval(rValue)
	implicit none

	real* 8, intent(inout) :: rValue

	! Container for return value from C call
	real*8 c_rValue
	common/rValue/ c_rValue

	! Evaluate objective
	call c_eval()

	! C++ call returns c_rValue via COMMON - I know this is ugly, but that's the way it works
	rValue = c_rValue

	end subroutine py_eval

