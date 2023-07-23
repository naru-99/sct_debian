# sct debian

動的解析(システムコールのシーケンスを取得)を行うために、debian のカーネルソースを改造

## how to カーネルビルド

1. virtual box のインストール

   > https://www.oracle.com/jp/virtualization/technologies/vm/downloads/virtualbox-downloads.html

2. debian のイメージファイルを取得(v 11.7 推奨)

   - v 11.7

     > https://drive.google.com/file/d/17TkRT2qbis8RJcdXv7xfuyeA_3evPU5o/view?usp=sharing

   - 最新版:
     > https://www.debian.org/distrib/index.ja.html

3. debian の OS を起動し、sudo ができるユーザの作成
4. 本ソースをダウンロード

```bash
git clone https://github.com/naru-99/sct_debian.git
```

5. make.sh の実行

```bash
cd sct_debian
sudo bash make.sh
```


## issue
### kernel/fork.cのpidtreeについて
udp通信のinitが完了する前に、プロセスの生成は行われるため、いつ頃からudp通信を用いて情報を送信するかは
```#define sci_wait_pid_num ((int)1000)```で決定しています。
しかし、上記はguiモードではうまくいきますが、cuiモードで起動した場合は通信を開始するタイミングが遅すぎるかもしれません。
その場合は、少し値を小さくすることで解決することができると思います。
