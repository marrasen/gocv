//go:build !matprofile
// +build !matprofile

package gocv

/*
#include <stdlib.h>
#include "core.h"
*/
import "C"
import (
	"errors"
	"unsafe"
)

// addMatToProfile does nothing if matprofile tag is not set.
func addMatToProfile(p C.Mat) {
	return
}

// newMat returns a new Mat from a C Mat
func newMat(p C.Mat) Mat {
	return Mat{p: p}
}

// Close the Mat object.
func (m *Mat) Close() error {
	var errMsg *C.char
	C.Mat_Close(m.p, &errMsg)
	m.p = nil
	m.d = nil
	if errMsg != nil {
		err := errors.New("Close encountered exception in external code: " + C.GoString(errMsg))
		C.free(unsafe.Pointer(errMsg))
		return err
	}
	return nil
}
