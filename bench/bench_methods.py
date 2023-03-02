import bench_methods_ext

if __name__ == "__main__":
    n = 10_000_000
    for _ in range(n):
        bench_methods_ext.no_input()

    for _ in range(n):
        bench_methods_ext.object_input(True)

    for _ in range(n):
        bench_methods_ext.object_input(obj=True)

    for _ in range(n):
        bench_methods_ext.multiple_object_input(True, True, True)

    for _ in range(n):
        bench_methods_ext.multiple_object_input(a=True, b=True, c=True)

    h = bench_methods_ext.hello()

    for _ in range(n):
        bench_methods_ext.bound_class_input(h)

    for _ in range(n):
        bench_methods_ext.bound_class_reference_input(h)
