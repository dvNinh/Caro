    Họ tên: Đinh Văn Ninh - Mã sinh viên: 21020362
# Dự án cuối kì môn LTNC - Game cờ Caro
## 1. Hướng dẫn cài đặt
- Dùng lệnh git clone để lưu thư mục về máy
- Mở file **Project LTNC.sln** bằng Visual Studio
- Run & Play
## 2. Mô tả chung
### *Luật chơi*:
- Hai người luân phiên đặt 1 quân của mình lên bàn cờ caro
- Người nào tạo được 5 quân liền nhau thành một hàng, cột hoặc đường chéo trước sẽ giành chiến thắng
### *Cách chơi*:
- Sử dụng con trỏ chuột để thao tác
- Bấm ESC để tạm dừng
### *Ý tưởng*:
- Sử dụng lớp **Map** để lưu giá trị tại mỗi ô trên bàn cờ
- Lớp **GameEngine** để kiểm tra lượt người chơi, sự kiện bấm phím và khả năng chiến thắng
- Lớp **Renderer** để hiển thị ra màn hình dựa vào map
- Lớp **Window** để tạo cửa sổ màn hình và nút bấm điều hướng
- Thuật toán của máy: Dựa vào vị trí vừa đặt của người chơi và máy kiểm tra khả năng thắng rồi đưa ra lựa chọn
## 3. Các chức năng đã cài đặt
- Hiệu ứng hình ảnh, âm thanh
- Menu điều khiển, tạm dừng
- Thông báo kết thúc game, có thể chơi lại
- Hai cách chơi: với máy hoặc với người
### *Video minh họa:* https://youtu.be/r5eIRT84WNM
## 4. Các kỹ thuật lập trình
- Con trỏ, mảng, chia tách file, hướng đối tượng
- Sử dụng một số lớp của thư viện SFML
- Học SFML tại https://www.sfml-dev.org/tutorials/2.5/
## 5. Kết luận
- Game đồ họa còn đơn giản, chưa có nhiều chức năng, code vẫn khá dài
### *Các điều tâm đắc rút ra được*:
- Tự mình lập trình và thiết kế
- Chia file theo từng chức năng
- Tạo được máy có khả năng chơi đơn giản
### *Hướng phát triển*:
- Cải thiện hình ảnh, âm thanh
- Tăng khả năng cho máy để có thể thắng đươc người
- Thêm một số tính năng như lưu game, nhập tên người chơi, các kiểu chơi khác,...

///_____DINHVANNINH___21020362_____///
