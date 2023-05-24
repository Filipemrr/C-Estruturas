n_candidates = int(input())

def sort_candidates(n_candidates):
    my_dict = {}

    for c in range(n_candidates):
        input_candidates = input()

        values = input_candidates.split()

        sum  = int(values[1]) + int(values[2]) + int(values[3])
        my_dict.update({f"{values[0]}": sum})

    sorted_dict = dict(sorted(my_dict.items(), key=lambda x: (-x[1], x[0])))
    



sort_candidates(n_candidates)