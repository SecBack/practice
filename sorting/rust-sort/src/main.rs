fn merge(original_array: &mut [i32], left_first_index: usize, left_end_index: usize, right_end_index: usize) {
    let left_size = left_end_index - left_first_index + 1;
    let right_size = right_end_index - left_end_index;

    let mut left_array = vec![0; left_size];
    let mut right_array = vec![0; right_size];

    for i in 0..left_size {
        left_array[i] = original_array[left_first_index + i];
    }
    for i in 0..right_size {
        right_array[i] = original_array[left_end_index + 1 + i];
    }

    let mut i = 0;
    let mut j = 0;
    let mut k = left_first_index;

    while i < left_size && j < right_size {
        if left_array[i] <= right_array[j] {
            original_array[k] = left_array[i];
            i += 1;
        } else {
            original_array[k] = right_array[j];
            j += 1;
        }
        k += 1;
    }

    while i < left_size {
        original_array[k] = left_array[i];
        i += 1;
        k += 1;
    }

    while j < right_size {
        original_array[k] = right_array[j];
        j += 1;
        k += 1;
    }
}

fn merge_sort(arr: &mut [i32], left: usize, right: usize) {
    if left < right {
        let mid = left + (right - left) / 2;
        merge_sort(arr, left, mid);
        merge_sort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

use rand::Rng;
use std::time::Instant;

fn generate_random_numbers(array: &mut [i32], upper_bound: i32) {
    let mut rng = rand::thread_rng();
    for i in array.iter_mut() {
        *i = rng.gen_range(1..=upper_bound);
    }
}

fn main() {
    const SIZE1: usize = 1000;
    const SIZE2: usize = 2000;
    const SIZE3: usize = 5000;
    const SIZE4: usize = 50000;
    const SIZE5: usize = 1000000;

    let mut numbers1 = vec![0; SIZE1];
    let mut numbers2 = vec![0; SIZE2];
    let mut numbers3 = vec![0; SIZE3];
    let mut numbers4 = vec![0; SIZE4];
    let mut numbers5 = vec![0; SIZE5];

    generate_random_numbers(&mut numbers1, 1000);
    generate_random_numbers(&mut numbers2, 2000);
    generate_random_numbers(&mut numbers3, 5000);
    generate_random_numbers(&mut numbers4, 50000);
    generate_random_numbers(&mut numbers5, 1000000);

    let start = Instant::now();
    merge_sort(&mut numbers1, 0, SIZE1 - 1);
    let duration = start.elapsed();
    println!("Time taken to sort numbers1: {:.6} seconds", duration.as_secs_f64());

    let start = Instant::now();
    merge_sort(&mut numbers2, 0, SIZE2 - 1);
    let duration = start.elapsed();
    println!("Time taken to sort numbers2: {:.6} seconds", duration.as_secs_f64());

    let start = Instant::now();
    merge_sort(&mut numbers3, 0, SIZE3 - 1);
    let duration = start.elapsed();
    println!("Time taken to sort numbers3: {:.6} seconds", duration.as_secs_f64());

    let start = Instant::now();
    merge_sort(&mut numbers4, 0, SIZE4 - 1);
    let duration = start.elapsed();
    println!("Time taken to sort numbers4: {:.6} seconds", duration.as_secs_f64());

    let start = Instant::now();
    merge_sort(&mut numbers5, 0, SIZE5 - 1);
    let duration = start.elapsed();
    println!("Time taken to sort numbers5: {:.6} seconds", duration.as_secs_f64());
}