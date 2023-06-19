(module
  (memory 2)
  (data $.rodata (i32.const 1024) "result=%d\0a\00")
  (global $__stack_pointer (mut i32) (i32.const 66576))
  (func (export "_start")
    (drop
      (i32.add
        (i32.const 1)
        (i32.const 2)
      )
    )
  )
)