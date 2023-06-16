(module
  (type $t0 (func (param i32 i32)))
  (type $t1 (func))
  (type $t2 (func (result i32)))
  (import "env" "jPrintf" (func $jPrintf (type $t0)))
  (func $__wasm_call_ctors (type $t1))
  (func $_start (type $t2) (result i32)
    (local $l0 i32) (local $l1 i32) (local $l2 i32) (local $l3 i32) (local $l4 i32) (local $l5 i32) (local $l6 i32) (local $l7 i32) (local $l8 i32) (local $l9 i32) (local $l10 i32) (local $l11 i32)
    global.get $__stack_pointer
    local.set $l0
    i32.const 16
    local.set $l1
    local.get $l0
    local.get $l1
    i32.sub
    local.set $l2
    local.get $l2
    global.set $__stack_pointer
    i32.const 1
    local.set $l3
    local.get $l2
    local.get $l3
    i32.store offset=12
    i32.const 2
    local.set $l4
    local.get $l2
    local.get $l4
    i32.store offset=8
    local.get $l2
    i32.load offset=12
    local.set $l5
    local.get $l2
    i32.load offset=8
    local.set $l6
    local.get $l5
    local.get $l6
    i32.add
    local.set $l7
    i32.const 1024
    local.set $l8
    local.get $l8
    local.get $l7
    call $jPrintf
    i32.const 0
    local.set $l9
    i32.const 16
    local.set $l10
    local.get $l2
    local.get $l10
    i32.add
    local.set $l11
    local.get $l11
    global.set $__stack_pointer
    local.get $l9
    return)
  (table $__indirect_function_table 1 1 funcref)
  (memory $memory 2)
  (global $__stack_pointer (mut i32) (i32.const 66576))
  (global $__dso_handle i32 (i32.const 1024))
  (global $__data_end i32 (i32.const 1035))
  (global $__global_base i32 (i32.const 1024))
  (global $__heap_base i32 (i32.const 66576))
  (global $__memory_base i32 (i32.const 0))
  (global $__table_base i32 (i32.const 1))
  (export "memory" (memory 0))
  (export "__wasm_call_ctors" (func $__wasm_call_ctors))
  (export "_start" (func $_start))
  (export "__dso_handle" (global 1))
  (export "__data_end" (global 2))
  (export "__global_base" (global 3))
  (export "__heap_base" (global 4))
  (export "__memory_base" (global 5))
  (export "__table_base" (global 6))
  (export "__indirect_function_table" (table 0))
  (data $.rodata (i32.const 1024) "result=%d\0a\00"))