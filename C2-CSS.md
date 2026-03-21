# CSS

## CSS

### Định nghĩa CSS

### Cú pháp CSS

## Các loại bộ chọn CSS
### Bộ chọn cơ bản (Basic Selectors)
Có 5 Bộ Chọn Cơ Bản:
  + **Type selector**: Sử dụng tên thẻ (như p, h1) để chọn tất cả các phần tử cùng loại.
  + **Class selector**: Sử dụng dấu chấm (.) trước tên lớp để chọn nhóm phần tử có cùng thuộc tính class.
  + **ID selector**: Sử dụng dấu thăng (#) trước tên danh hiệu để chọn duy nhất một phần tử có id tương ứng.
  + **Universal selector**: Sử dụng dấu sao (*) để khớp với mọi phần tử HTML.
  + **Selector list**: Gom nhóm các bộ chọn có cùng khối khai báo bằng dấu phẩy
### Bộ chọn thuộc tính (Attribute selectors):
Chọn các phần tử dựa trên sự hiện diện hoặc giá trị của thuộc tính (ví dụ: [type="text"])
### Bộ chọn kết hợp (Combinators):
Chọn các phần tử dựa trên mối quan hệ giữa chúng, bao gồm: hậu duệ (khoảng cách), con trực hệ (>), anh em kề nhau (+), và anh em kế tiếp (~)
### Bộ chọn lớp giả (Pseudo-classes) và phần tử giả (Pseudo-elements):
- Lớp giả (:) dùng để định kiểu trạng thái cụ thể (như :hover, :active)
- Phần tử giả (::) dùng để định kiểu một phần cụ thể của phần tử (như ::first-line, ::after)
### Bộ chọn lồng nhau (& nesting selector): 
Được sử dụng để giảm việc lặp lại tên bộ chọn cha trong ngữ cảnh có liên kết cha-con.
## Độ cụ thể (Selector Specificity)
- **Độ cụ thể** là giá trị dùng để xác định mức độ ưu tiên của các bộ chọn khi xảy ra xung đột thuộc tính trong cùng một nguồn CSS
- Giải thuật tính độ cụ thể (A, B, C): Trình duyệt so khớp dựa trên ba thành phần theo thứ tự ưu tiên từ A đến C:
  + **A (ID-like)**: Số lượng bộ chọn ID (trọng số 100)
  + **B (Class-like)**: Số lượng bộ chọn lớp, thuộc tính và lớp giả (trọng số 10)
  + **C (Element-like)**: Số lượng bộ chọn phần tử và phần tử giả (trọng số 1)
**Thứ tự ưu tiên từ cao đến thấp:**
1. **!important**: Có ưu tiên cao nhất (vô hạn), nhưng không khuyến khích sử dụng
2. **Inline style (Kiểu nội tuyến)**: Trọng số 1000
3. **ID**: Trọng số 100
4. **Class / Attribute / Pseudo-class**: Trọng số 10
5. **Element / Pseudo-element**: Trọng số 1
6. **Universal selector (*)**: Có độ cụ thể bằng 0
