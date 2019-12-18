import java.io.*;
import java.lang.Math;

public class Main {
    //public Main() throws IOException {
    //}

    //

    private static int lg(double x) {
        return ((int) (Math.log(x) / Math.log(2.0)));
    }

    private static File Table = new File("et.txt");
    private static FileWriter Writer;

    static {
        try {
            Writer = new FileWriter(Table, false);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private static void Decoding() {
        int n;
        try {
            FileReader Reader = new FileReader("et.txt");
            BufferedReader br = new BufferedReader(Reader);
            Reader = new FileReader(Table);
            br = new BufferedReader(Reader);
            String[] codes = new String[256];

            File Result = new File("dec.txt");
            Writer = new FileWriter(Result);

            for (int i = 0; i < 256; i++) {
                codes[i] = br.readLine();
            }
            //Scanner fr = new Scanner (new File("resulttt.txt"));
            //n=fr.nextInt();
            BufferedReader bufferedReader = new BufferedReader(new FileReader("resulttt.txt"));
            char chr = (char) bufferedReader.read();

            int buf = 0;
            n = Integer.parseInt(new String() + chr);
            int symbyle = bufferedReader.read();
            while (symbyle != -1) {
                symbyle = bufferedReader.read();
                String code = "";
                // code=code+(char)symbyle;
                while (symbyle != -1 && ((char) symbyle != ' ')) {
                    code = code + (char) symbyle;
                    symbyle = bufferedReader.read();
                    //System.out.println(code);
                }

                int index = 0;
                if (!code.equals(""))
                    for (int t = 0; t < 256; t++) {
                        index = t;
                        if (codes[t].equals(code)) break;
                    }
                if (!code.equals(""))
                    for (int t = 0; t <= index; t++) {
                        System.out.print(n);
                        Writer.write("" + n);
                        Writer.flush();
                    }

                if (n == 0) n = 1;
                else n = 0;
            }
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }

    }

    private static void ElliasTable() throws IOException {
        Writer.write("0\n");
        String code;
        for (int i = 2; i < 256; i++) {
            code = Integer.toString(i, 2);
            int n = i;
            boolean play = true;
            while (play) {
                switch (lg(n)) {
                    case 2:
                        code = "10" + code;
                        play = false;
                        break;
                    case 3:
                        code = "11" + code;
                        play = false;
                        break;
                    case 4:
                        code = "100" + code;
                        n = lg(n);
                        break;
                    case 5:
                        code = "101" + code;
                        n = lg(n);
                        break;
                    case 6:
                        code = "110" + code;
                        n = lg(n);
                        break;
                    case 7:
                        code = "111" + code;
                        n = lg(n);
                        break;
                    default:
                        play = false;
                        break;
                    //n = lg(n);
                }
            }
            code = code + "0\n";
            Writer.write(code);
            Writer.flush();
        }
    }

    private static void Compression(String SourceName, String ResultName) throws IOException {
        double sizeBefore;
        double sizeAfter;
        double koef;

        File From = new File(SourceName);
        FileReader Reader = new FileReader(From);
        BufferedReader br = new BufferedReader(Reader);
        String line = br.readLine();

        sizeBefore = line.length();

        char[] bin;
        bin = line.toCharArray();
        line = "";
        int[] numbers = new int[1024];
        int index = 0;
        for (int i = 0; i < sizeBefore; i++) {
            int serie = 0;
            int serie1 = 0;
            if (i + 1 > sizeBefore) {
                break;
            }

            while (i < bin.length && bin[i] == '1') {
                serie1++;
                i++;
            }
            /*
            if (bin[i] == '1' && bin[i + 1] == '1') {
                    line = line + " 1";
                    numbers[index] = 0;
                    index++;
                    i++;
                    continue;
                }else if(bin[i] == '1'){
                    line = line + " ";
                    continue;
                }
                */
            if (serie1 > 0) {
                i--;
                line = line + serie1;
                numbers[index] = serie1;
                index++;
            }
            while (i < bin.length && bin[i] == '0') {
                serie++;
                i++;
            }
            if (serie > 0) {
                i--;
                line = line + serie;
                numbers[index] = serie;
                //System.out.println(numbers[index]);
                index++;
            }
        }
        numbers[index] = -1;
        //System.out.println(line);


        Reader = new FileReader(Table);
        br = new BufferedReader(Reader);
        String[] codes = new String[256];
        for (int i = 0; i < 256; i++) {
            codes[i] = br.readLine();
        }
        File Result = new File(ResultName);
        Writer = new FileWriter(Result);
        line = "";
        Writer.write(bin[0] + " ");
        for (int i = 0; numbers[i] != -1; i++) {

            line += codes[numbers[i] - 1] + " ";
            Writer.write(codes[numbers[i] - 1] + " ");
            Writer.flush();
        }
        sizeAfter = line.length();
        koef = (sizeAfter / sizeBefore) * 100;
        System.out.println("Коэффициент сжатия");
        System.out.println(koef);
    }

    public static void main(String[] args) throws IOException {
        Main.ElliasTable();
        Main.Compression("src.txt", "resulttt.txt");
        System.out.println("\nДекодированный файл:");
        Decoding();
        System.out.println("\nИсходный файл:");
        Decoding();

        File From = new File("src.txt");
        FileReader Reader = new FileReader(From);
        BufferedReader br = new BufferedReader(Reader);
        String line = br.readLine();
        File FromD = new File("resulttt.txt");
        FileReader ReaderD = new FileReader(FromD);
        BufferedReader brD = new BufferedReader(ReaderD);
        String lineD = brD.readLine();

        double sizeBefore = line.length();
        double sizeBeforeD = lineD.length();

        char[] bin;
        char[] binD;
        bin = line.toCharArray();
        binD = lineD.toCharArray();
        int count = 0;
        int[] numbers = new int[10240];
        for (int i = 0; i < sizeBefore; i++) {
            if (bin[i] == bin[i])
                count++;
        }
        if(count==sizeBefore)
            System.out.print("\nДекодированный файл совпадает с исходным");
        else
            System.out.print("\nДекодированный файл не совпадает с исходным");
    }

}
