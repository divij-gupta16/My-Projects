function Z = SYK(N)
    sigma_x = [0 1; 1 0];
    sigma_z = [1 0;0 -1];
    Z = cell(N,1);
%    H = zeros(2^N);
%    X = cell(2^N,1);
%    g = zeros(2*N);
%    j = zeros(2*N);
    for c = 1:N
        Z{c} = kron_mult(kron_exp(sigma_z, c-1),sigma_x,eye(2^(N-c)));
    end
%     for i = 1:(N-1)
%         H = H - j(i)*(Z{i}*Z{i+1} + X{i});
%     end
%    H = H - j(N)*X{N};
%     if geometry == "loop"
%         J = 0.2*rand - 0.1;
%         H = H - J*Z{N}*Z{1};
%     end
    %disp(H);
end