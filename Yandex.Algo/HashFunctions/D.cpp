using System;
using System.ComponentModel.Design;

class Program
{
    static void Main(string[] args)
    {
        Console.WriteLine("Введите кол-во элементов массива");
        int n = Convert.ToInt32(Console.ReadLine());
        double[] a = new double[n];
        if (n == 0)
        {
            Console.WriteLine("Задан пустой массив, дальнейшее выполнение программы невозможно");
        }
        else
        {
        
                string k;
                Console.WriteLine("Введите массив a");
                for (int i = 0; i < n; i++)
                {
                    k = Console.ReadLine();                    
                    a[i] = double.Parse(k);
                }
                double amax = a[0];
                int imax = 0;
                double amin = a[0];
                for (int i = 0; i < n; i++)
                {
                    if (a[i] > amax)
                    {
                        amax = a[i];
                        imax = i;
                    }
                    if (a[i] < amin)
                    {
                        amin = a[i];
                    }
                }
                Console.WriteLine("Максимальный элемент массива");
                Console.WriteLine(amax);
                Console.WriteLine("Минимальный элемент массива");
                Console.WriteLine(amin);
                for (int i = imax+1; i < n; i++)
                {
                    a[i] = amin;
                }
                Console.WriteLine("Измененный массив");
                for (int i = 0; i < n; i++)
                {
                    Console.WriteLine($"{a[i]} ");
                }
            
        }
    }
}