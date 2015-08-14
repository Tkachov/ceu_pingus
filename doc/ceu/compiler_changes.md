# Compiler changes

## Classes amount fix

July 31, 2015 fix: line 6517
```
        TP.types.tceu_ncls.len = TP.n2bytes(#ENV.clss_cls*2)
        --                                               *2 (signed => unsigned)
```

Fixes classes bug when use of a lot of classes could've result in segfault.

## Unsafe access to pointer warning

June 5, 2015 change: line 8923
```
        WRN(false, me, 1107,
            'unsafe access to pointer "'..me.var.id..'" across `'..
                acc_id..'´ ('..acc.ln[1]..' : '..acc.ln[2]..')')
```

Warning instead of assert.

## Not permitted inside `every` warning

July 15, 2015 change: line 9404
```
        WRN((not evr) or AST.isParent(evr,blk), me,
                'not permitted inside `every´')
```

Makes compiler forgive use of `break` in `every`. I think I actually don't use `break` in `every` anymore.

## Stack size increased

August 11, 2015 change: line 920
```
    #define CEU_STACK_MAX   1024*sizeof(tceu_stk)
```

Bigger stack so no crash occur after the level is played. Probably such crash still could occur, but in user's levels where more Pingus than in story mode levels appear.