use std::io::{self, Result, Write};

fn main() -> Result<()> {
    let stdin = io::stdin();
    let stdout = io::stdout();
    let mut reader = cp::Reader::new(stdin.lock());
    let mut writer = io::BufWriter::new(stdout.lock());

    let n: i64 = reader.read();
    let mut a: Vec<i64> = Vec::new();
    for _ in 0..n {
        a.push(reader.read());
    }

    writeln!(writer, "{}", num_inversion(&mut a))?;
    Ok(())
}

fn num_inversion(a: &mut Vec<i64>) -> i64 {
    let mut num: i64 = 0;

    fn merge(a: &mut [i64], l: usize, r: usize, num: &mut i64) {
        let m = l + (r - l) / 2;
        let mut i = l;
        let mut j = m;

        let mut tmp: Vec<i64> = Vec::new();

        while i < m && j < r {
            if a[i] <= a[j] {
                tmp.push(a[i]);
                i += 1;
            } else {
                tmp.push(a[j]);
                j += 1;
                *num += (m - i) as i64;
            }
        }

        while i < m {
            tmp.push(a[i]);
            i += 1;
        }

        while j < r {
            tmp.push(a[j]);
            j += 1;
        }

        a[l..r].clone_from_slice(&tmp[0..(r - l)]);
    }

    fn merge_sort(a: &mut Vec<i64>, l: usize, r: usize, num: &mut i64) {
        if l >= r - 1 {
            return;
        }

        let m = l + (r - l) / 2;
        merge_sort(a, l, m, num);
        merge_sort(a, m, r, num);
        merge(a, l, r, num);
    }

    merge_sort(a, 0, a.len(), &mut num);
    num
}
