from functools import wraps


def count_calls(func):

    @wraps(func)
    def decorated(*args, **kwargs):
        decorated.calls_count += 1
        return func(*args, **kwargs)

    decorated.count_calls = 0
    return decorated


@count_calls
def foo(x, y):
    return x + y


def main():
    foo(1, 2)
    foo(3, 4)
    foo(4, 5)
    foo(foo.calls_count)


if __name__ == '__main__':
    main()
